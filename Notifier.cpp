#include "Notifier.h"

std::unique_ptr<Notifier> createNotifier(NotifierType type, const std::string& filename)
{
    switch (type)
    {
    case NotifierType::email:
        return std::make_unique<EmailNotifier>();
    case NotifierType::sms:
        return std::make_unique<SmsNotifier>();
    case NotifierType::console:
        return std::make_unique<ConsoleNotifier>();
    case NotifierType::file:
        return std::make_unique<FileNotifier>(filename);
    }
    return nullptr;
}

std::unique_ptr<Notifier> createNotifier(const std::string &type, const std::string& filename)
{
    std::string normalizedType = type;
    std::transform(normalizedType.begin(), normalizedType.end(), normalizedType.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    if (normalizedType == "email")
    {
        return createNotifier(NotifierType::email);
    }
    else if (normalizedType == "sms")
    {
        return createNotifier(NotifierType::sms);
    }
    else if (normalizedType == "console")
    {
        return createNotifier(NotifierType::console);
    }
    else if (normalizedType == "file")
    {
        return createNotifier(NotifierType::file, filename);
    }
    else
    {
        return nullptr;
    }
}
 
void EmailNotifier::Send(const std::string &text) const
{
    std::cout << "Email: " << text << std::endl;
}

void SmsNotifier::Send(const std::string &text) const
{
    std::cout << "Sms: " << text << std::endl;
}

void ConsoleNotifier::Send(const std::string &text) const
{
    std::cout << "Console: " << text << std::endl;
}

FileNotifier::FileNotifier(const std::string& filename) : filename_(filename){}

void FileNotifier::Send(const std::string& text) const
{
    std::ofstream file(filename_, std::ios_base::app);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename_);
    }

    file << text << std::endl;

    if (!file)
    {
        throw std::runtime_error("Failed to write file: " + filename_);
    }
}