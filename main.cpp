#include <iostream>

#include "absl/log/globals.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main(int argc, char* argv[]) {
    absl::InitializeLog();
    absl::SetStderrThreshold(absl::LogSeverityAtLeast::kInfo);
    auto lang = "C++";
    LOG(INFO) << "Hello and welcome to " << lang << "!";


    // use abseil strings to print a message
    std::string message2 = absl::StrCat(" first ", " second ");
    std::string message3 = absl::StrCat(" first ", " second ", " third ");
    std::string message4 = absl::StrCat(" first ", " second ", " third ", " fourth ");

    LOG(INFO) << message2;
    LOG(INFO) << message3;
    LOG(INFO) << message4;
    return 0;
}