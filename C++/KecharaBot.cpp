#include <dpp/dpp.h>
#include <iostream>
#include <dpp/fmt/format.h>
#include "VigenereCipher.h"

int main()
{
    try {
        dpp::cluster bot("OTMyNzcyNzM2MjY1MjQ4Nzc4.YeX2Tg.RYv8iKXVdke2ySpubQMCpmuRTs4");

        bot.on_interaction_create([&bot](const dpp::interaction_create_t& event) {
            if (event.command.type == dpp::it_application_command) {
                dpp::command_interaction cmd_data = std::get<dpp::command_interaction>(event.command.data);
                /* Check which command they ran */
                if (cmd_data.name == "blep") {
                    std::string key = std::get<std::string>(event.get_parameter("key"));
                    std::string plainText = std::get<std::string>(event.get_parameter("message"));
                    NoxLib::VigenereCipher vc;
                    vc.aOffset = 0;
                    std::string encodedText = vc.encode(plainText, key);
                    event.reply(dpp::ir_channel_message_with_source, fmt::format("Your encoded text is: {}", encodedText));
                }
                if (cmd_data.name == "vigEncode")
                {
                    std::string key = std::get<std::string>(event.get_parameter("key"));
                    std::string plainText = std::get<std::string>(event.get_parameter("message"));
                    NoxLib::VigenereCipher vc;
                    std::string encodedText = vc.encode(plainText, key);
                    event.reply(dpp::ir_channel_message_with_source, fmt::format("Your encoded text is: {}", encodedText));
                }
            }
            });


        bot.on_ready([&bot](const dpp::ready_t& event) {
            dpp::slashcommand newcommand;
            /* Create a new global command on ready event */
            newcommand.set_name("blep")
                .set_description("Encode message with VigCipher")
                .set_application_id(bot.me.id)
                .add_option(
                    dpp::command_option(dpp::co_string, "key", "The encoding key", true)
                )
                .add_option(
                    dpp::command_option(dpp::co_string, "message", "The plain text", true));

            /* Register the command */
            bot.global_command_create(newcommand);


            dpp::slashcommand vigEncode;
            vigEncode.set_name("vigEncode")
                .set_description("Encode message with VigCipher")
                .set_application_id(bot.me.id)
                .add_option(
                    dpp::command_option(dpp::co_string, "key", "The encoding key", true)
                )
                .add_option(
                    dpp::command_option(dpp::co_string, "message", "The plain text", true));
            bot.global_command_create(vigEncode);

            bot.log(dpp::ll_info, "Logged in as " + bot.me.username);
        });

        bot.on_message_create([&bot](const dpp::message_create_t& event) {
            if (event.msg.content == "Hello") {
                bot.message_create(dpp::message(event.msg.channel_id, "I live!"));
            }
        });

        bot.on_log([](const dpp::log_t& event) {
            if (event.severity > dpp::ll_trace) {
                std::cout << dpp::utility::loglevel(event.severity) << ": " << event.message << "\n";
            }
        });

        bot.start(false);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
