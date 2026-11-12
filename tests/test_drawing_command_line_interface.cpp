/***************************************************************************
 *            tests/test_drawing_command_line_interface.cpp
 *
 *  Copyright  2008-26  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne Drawing.
 *
 *  Ariadne Drawing is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne Drawing is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne Drawing. If not, see <https://www.gnu.org/licenses/>.
 */

/** @file tests/test_drawing_command_line_interface.cpp
 *  @brief Test drawing command line interface behavior.
 */

#include "drawing/drawing_command_line_interface.hpp"
#include "logging/logging.hpp"
#include "threading/thread_manager.hpp"
#include "ariadne-testing.hpp"
#include <type_traits>

using namespace Ariadne;

class TestCommandLineInterface : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_inherited_profile() {
        static_assert(std::is_base_of_v<ThreadingCommandLineInterface, DrawingCommandLineInterface>);
        DrawingCommandLineInterface command_line;
        ARIADNE_TESTING_PROVE(command_line.acquire({
            "",
            "--scheduler","immediate",
            "--concurrency","0",
            "--verbosity","3",
            "--theme","none",
            "--drawer","none",
            "--rendering","none"
        }));
        ARIADNE_TESTING_EXPECT_EQUAL(ThreadManager::instance().concurrency(),0u);
        ARIADNE_TESTING_EXPECT_EQUAL(Logger::instance().configuration().verbosity(),3u);
        ARIADNE_TESTING_PROVE(not Logger::instance().configuration().theme().has_style());
        Logger::instance().use_nonblocking_scheduler();
    }

    Void test_profile() {
        ARIADNE_TESTING_EXPECT_NO_THROW(DrawingCommandLineInterface());
        DrawingCommandLineInterface command_line;
        ARIADNE_TESTING_PROVE(command_line.acquire({""}));
    }

    Void test_from_c_arguments() {
        DrawingCommandLineInterface command_line;
        const char* argv1[]={""};
        ARIADNE_TESTING_PROVE(command_line.acquire(1,argv1));
        const char* argv2[]={"",""};
        ARIADNE_TESTING_PROVE(not command_line.acquire(2,argv2));
    }

    Void test_drawer_parsing() {
        DrawingCommandLineInterface command_line;

        ARIADNE_TESTING_PROVE(command_line.acquire({"","-d","box"}));
        ARIADNE_TESTING_PROVE(command_line.acquire({"","--drawer","box"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d","bx"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d","affine"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d","affine@e"}));
        ARIADNE_TESTING_PROVE(command_line.acquire({"","-d","affine@2"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d","grid"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d","grid@e"}));
        ARIADNE_TESTING_PROVE(command_line.acquire({"","-d","grid@2"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d","gri@2"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d"}));
        ARIADNE_TESTING_PROVE(command_line.acquire({"","-d","none"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-d","affine@-1"}));
    }

    Void test_rendering_parsing() {
        DrawingCommandLineInterface command_line;

        ARIADNE_TESTING_PROVE(command_line.acquire({"","-g","default"}));
        ARIADNE_TESTING_PROVE(command_line.acquire({"","--rendering","default"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-g","default_rendering"}));
        ARIADNE_TESTING_PROVE(command_line.acquire({"","--rendering","none"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-g","wrong"}));
        ARIADNE_TESTING_PROVE(command_line.acquire({"","-g","none"}));
        ARIADNE_TESTING_PROVE(not command_line.acquire({"","-g"}));
    }

    Void test_composed_parsing() {
        ThreadManager::instance().set_concurrency(0);
        DrawingCommandLineInterface command_line;

        ARIADNE_TESTING_PROVE(command_line.acquire({
            "",
            "--scheduler","immediate",
            "--concurrency","0",
            "--verbosity","4",
            "--theme","none",
            "--rendering","none"
        }));
        ARIADNE_TESTING_EXPECT_EQUAL(
            ThreadManager::instance().concurrency(),0u);
        ARIADNE_TESTING_EXPECT_EQUAL(
            Logger::instance().configuration().verbosity(),4u);
        ARIADNE_TESTING_PROVE(
            not Logger::instance().configuration().theme().has_style());

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

        ARIADNE_TESTING_PROVE(command_line.acquire({
            "",
            "--custom-value","3",
            "--custom-flag",
            "--verbosity","2"
        }));
        ARIADNE_TESTING_EXPECT_EQUAL(custom_value,3u);
        ARIADNE_TESTING_PROVE(custom_flag);
        ARIADNE_TESTING_EXPECT_EQUAL(
            Logger::instance().configuration().verbosity(),2u);

        ARIADNE_TESTING_PROVE(not command_line.acquire({
            "",
            "--custom-value","-1"
        }));
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_drawing_command_line_interface");
    ARIADNE_TESTING_ADD_TEST(TestCommandLineInterface, test_inherited_profile);
    ARIADNE_TESTING_ADD_TEST(TestCommandLineInterface, test_profile);
    ARIADNE_TESTING_ADD_TEST(TestCommandLineInterface, test_from_c_arguments);
    ARIADNE_TESTING_ADD_TEST(TestCommandLineInterface, test_drawer_parsing);
    ARIADNE_TESTING_ADD_TEST(TestCommandLineInterface, test_rendering_parsing);
    ARIADNE_TESTING_ADD_TEST(TestCommandLineInterface, test_composed_parsing);
    ARIADNE_TESTING_ADD_TEST(TestCommandLineInterface, test_local_contribution);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
