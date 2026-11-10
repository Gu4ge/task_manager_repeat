#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <cctype>
#include <algorithm>
#include <fstream>

enum NotifierType
{
    email,
    sms,
    console,
    file
};

class Notifier
{
public:
    virtual ~Notifier() = default;
    virtual void Send(const std::string &text) const = 0;
};

class EmailNotifier : public Notifier
{
public:
    void Send(const std::string &text) const override;
};

class SmsNotifier : public Notifier
{
public:
    void Send(const std::string &text) const override;
};

class ConsoleNotifier : public Notifier
{
public:
    void Send(const std::string &text) const override;
};

class FileNotifier : public Notifier
{
public:
    explicit FileNotifier(const std::string &filename = "events.log");
    void Send(const std::string &text) const override;

private:
    std::string filename_;
};

std::unique_ptr<Notifier> createNotifier(NotifierType type, const std::string &filename = "events.log");
std::unique_ptr<Notifier> createNotifier(const std::string &type, const std::string &filename = "events.log");