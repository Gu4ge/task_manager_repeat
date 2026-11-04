#include "Notifier.h"

std::unique_ptr<Notifier> createNotifier(NotifierType type)
{
    switch (type)
    {
    case NotifierType::email:
        return std::make_unique<EmailNotifier>();
    case NotifierType::sms:
        return std::make_unique<SmsNotifier>();
    case NotifierType::console:
        return std::make_unique<ConsoleNotifier>();
    }
    return nullptr;
}

std::unique_ptr<Notifier> createNotifier(const std::string &type)
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