/***************************************************************************
 *            test_drawing_command_line_interface.cpp
 *
 *  Copyright  2008-26  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne.
 *
 *  Ariadne is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 */

#include "drawing/drawing_command_line_interface.hpp"
#include "logging/logging.hpp"
#include "threading/thread_manager.hpp"
#include "macro/testing.hpp"
#include <type_traits>

using namespace Ariadne;

class TestCommandLineInterface {
  public:
    Void test() {
        ARIADNE_TEST_CALL(test_inherited_profile())
        ARIADNE_TEST_CALL(test_profile())
        ARIADNE_TEST_CALL(test_from_c_arguments())
        ARIADNE_TEST_CALL(test_drawer_parsing())
        ARIADNE_TEST_CALL(test_rendering_parsing())
        ARIADNE_TEST_CALL(test_composed_parsing())
        ARIADNE_TEST_CALL(test_local_contribution())
    }

    Void test_inherited_profile() {
        static_assert(std::is_base_of_v<ThreadingCommandLineInterface, DrawingCommandLineInterface>);
        DrawingCommandLineInterface command_line;
        ARIADNE_TEST_ASSERT(command_line.acquire({
            "",
            "--scheduler","immediate",
            "--concurrency","0",
            "--verbosity","3",
            "--theme","none",
            "--drawer","none",
            "--rendering","none"
        }))
        ARIADNE_TEST_EQUALS(ThreadManager::instance().concurrency(),0u)
        ARIADNE_TEST_EQUALS(Logger::instance().configuration().verbosity(),3u)
        ARIADNE_TEST_ASSERT(not Logger::instance().configuration().theme().has_style())
        Logger::instance().use_nonblocking_scheduler();
    }

    Void test_profile() {
        ARIADNE_TEST_EXECUTE(DrawingCommandLineInterface())
        DrawingCommandLineInterface command_line;
        ARIADNE_TEST_ASSERT(command_line.acquire({""}))
    }

    Void test_from_c_arguments() {
        DrawingCommandLineInterface command_line;
        const char* argv1[]={""};
        ARIADNE_TEST_ASSERT(command_line.acquire(1,argv1))
        const char* argv2[]={"",""};
        ARIADNE_TEST_ASSERT(not command_line.acquire(2,argv2))
    }

    Void test_drawer_parsing() {
        DrawingCommandLineInterface command_line;

        ARIADNE_TEST_ASSERT(command_line.acquire({"","-d","box"}))
        ARIADNE_TEST_ASSERT(command_line.acquire({"","--drawer","box"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d","bx"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d","affine"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d","affine@e"}))
        ARIADNE_TEST_ASSERT(command_line.acquire({"","-d","affine@2"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d","grid"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d","grid@e"}))
        ARIADNE_TEST_ASSERT(command_line.acquire({"","-d","grid@2"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d","gri@2"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d"}))
        ARIADNE_TEST_ASSERT(command_line.acquire({"","-d","none"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-d","affine@-1"}))
    }

    Void test_rendering_parsing() {
        DrawingCommandLineInterface command_line;

        ARIADNE_TEST_ASSERT(command_line.acquire({"","-g","default"}))
        ARIADNE_TEST_ASSERT(command_line.acquire({"","--rendering","default"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-g","default_rendering"}))
        ARIADNE_TEST_ASSERT(command_line.acquire({"","--rendering","none"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-g","wrong"}))
        ARIADNE_TEST_ASSERT(command_line.acquire({"","-g","none"}))
        ARIADNE_TEST_ASSERT(not command_line.acquire({"","-g"}))
    }

    Void test_composed_parsing() {
        ThreadManager::instance().set_concurrency(0);
        DrawingCommandLineInterface command_line;

        ARIADNE_TEST_ASSERT(command_line.acquire({
            "",
            "--scheduler","immediate",
            "--concurrency","0",
            "--verbosity","4",
            "--theme","none",
            "--rendering","none"
        }))
        ARIADNE_TEST_EQUALS(
            ThreadManager::instance().concurrency(),0u)
        ARIADNE_TEST_EQUALS(
            Logger::instance().configuration().verbosity(),4u)
        ARIADNE_TEST_ASSERT(
            not Logger::instance().configuration().theme().has_style())

        Logger::instance().use_nonblocking_scheduler();
    }

    Void test_local_contribution() {
        Nat custom_value=0u;
        Bool custom_flag=false;

        DrawingCommandLineInterface command_line;
        command_line.add(CommandLineContribution(
            "test-local",
            {
                make_valued_argument_parser(
                    "",
                    "custom-value",
                    "Set a custom non-negative integer",
                    [&custom_value](String const& value) -> VoidFunction {
                        Int const parsed=std::stoi(value);
                        if (parsed < 0) {
                            throw std::runtime_error(
                                "negative custom value");
                        }
                        return [&custom_value,parsed] {
                            custom_value=static_cast<Nat>(parsed);
                        };
                    }),
                make_unvalued_argument_parser(
                    "",
                    "custom-flag",
                    "Enable a custom flag",
                    [&custom_flag] {
                        custom_flag=true;
                    })
            }));

        ARIADNE_TEST_ASSERT(command_line.acquire({
            "",
            "--custom-value","3",
            "--custom-flag",
            "--verbosity","2"
        }))
        ARIADNE_TEST_EQUALS(custom_value,3u)
        ARIADNE_TEST_ASSERT(custom_flag)
        ARIADNE_TEST_EQUALS(
            Logger::instance().configuration().verbosity(),2u)

        ARIADNE_TEST_ASSERT(not command_line.acquire({
            "",
            "--custom-value","-1"
        }))
    }
};

Int main() {
    TestCommandLineInterface().test();
    return ARIADNE_TEST_FAILURES;
}
