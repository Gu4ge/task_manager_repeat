#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <cctype>
#include <algorithm>

enum NotifierType{email, sms, console};

class Notifier
{
public:
    virtual ~Notifier() = default;
    virtual void Send(const std::string& text) const = 0;
};

class EmailNotifier : public Notifier
{
public:
    void Send(const std::string& text) const override;
};

class SmsNotifier : public Notifier
{
public:
    void Send(const std::string& text) const override;
};

class ConsoleNotifier : public Notifier
{
public:
    void Send(const std::string& text) const override;
};

std::unique_ptr<Notifier> createNotifier(NotifierType type);
std::unique_ptr<Notifier> createNotifier(const std::string& type);