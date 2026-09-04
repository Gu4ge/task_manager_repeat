#include "Notifier.h"

std::unique_ptr<Notifier> createNotifier(NotifierType type){
    std::unique_ptr<Notifier> notifier;
    switch (type)
    {
    case email:
        return std::make_unique<EmailNotifier>();
    case sms:
        return std::make_unique<SmsNotifier>();
    case console:
        return std::make_unique<ConsoleNotifier>();
    }
    return nullptr;
}

void EmailNotifier::Send(const std::string& text) const{
    std::cout << "Email: " << text << std::endl;
}

void SmsNotifier::Send(const std::string& text) const{
    std::cout << "Sms: " << text << std::endl;
}

void ConsoleNotifier::Send(const std::string& text) const{
    std::cout << "Console: " << text << std::endl;
}