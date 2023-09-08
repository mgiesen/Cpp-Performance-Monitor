/*
 * File: Performance.h
 * Project: CppPerformanceTracker
 * File Created: Thursday, 7th September 2023, 9:00 pm
 * Author: Maximilian Giesen
 *
 * License: MIT License
 * Source: https://github.com/mgiesen/CppPerformanceMonitor
 *
 * Description:
 * A lightweight performance monitoring class for C++ programs
 */

#pragma once

#include <sstream>
#include <locale>
#include <iostream>
#include <chrono>
#include <deque>
#include <string>
#include <iomanip>

class Performance
{
private:
    // Constant for uninitialized values
    static const int UNINITIALIZED = -1;

    // Structure for process information
    struct process
    {
        std::string name = "";
        int resolution = UNINITIALIZED;
        int time = UNINITIALIZED;
        std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    };

    // List of tracked processes
    std::deque<process> processes;

    // Function for formatting integer values
    std::string format_integer_thousand_separator(int value)
    {
        std::ostringstream oss;
        oss.imbue(std::locale(""));
        oss << std::fixed << value;
        return oss.str();
    }

public:
    // Enumeration for time resolution
    enum struct resolution
    {
        seconds = 1,
        milliseconds = 2,
        microseconds = 3,
        nanoseconds = 4
    };

    // Starts a new process and returns its ID
    int start(std::string process_name = "UNKNOWN", resolution res = resolution::milliseconds)
    {
        const int step_position = processes.size();
        process this_step;
        this_step.name = process_name;
        this_step.resolution = static_cast<int>(res);
        processes.push_back(this_step);
        return step_position;
    }

    // Stops a process and updates its runtime information
    int stop(const int process_id)
    {
        try
        {
            std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
            std::chrono::high_resolution_clock::time_point start_time = processes.at(process_id).start_time;

            switch (static_cast<resolution>(processes.at(process_id).resolution))
            {
            case resolution::seconds:
                processes.at(process_id).time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
                break;
            case resolution::milliseconds:
                processes.at(process_id).time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
                break;
            case resolution::microseconds:
                processes.at(process_id).time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
                break;
            case resolution::nanoseconds:
                processes.at(process_id).time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
                break;
            }

            if (processes.at(process_id).time > UNINITIALIZED)
            {
                return EXIT_SUCCESS;
            }
            else
            {
                throw std::runtime_error("Error: Invalid Performance Operation");
            }
        }
        catch (const std::exception &)
        {
            throw std::runtime_error("Error: Invalid Performance Operation");
        }
    }

    // Displays the results of all processes
    void show_results(std::string table_title = "Performance List")
    {
        std::ostringstream oss;
        const std::string table_seperator = "---------------------------------------------------------------------------";

        oss << std::endl
            << table_seperator << std::endl;
        oss << std::setw(table_seperator.length() / 2 + table_title.length() / 2) << table_title << std::endl;
        oss << table_seperator << std::endl
            << std::endl;

        if (processes.size() == 0)
        {
            oss << "\t"
                << "No Events Tracked" << std::endl;
        }
        else
        {
            for (auto step : processes)
            {
                std::string suffix_string = "";
                std::string runtime = "";

                switch (static_cast<resolution>(step.resolution))
                {
                case resolution::seconds:
                    suffix_string = "s";
                    break;
                case resolution::milliseconds:
                    suffix_string = "ms";
                    break;
                case resolution::microseconds:
                    suffix_string = "microseconds"; // Missing UTF-8 solution
                    break;
                case resolution::nanoseconds:
                    suffix_string = "ns";
                    break;
                }

                if (step.time == -1)
                {
                    runtime = "STILL RUNNING";
                    suffix_string = "";
                }
                else
                {
                    runtime = format_integer_thousand_separator(step.time);
                }

                const std::string runtime_string = runtime + " " + suffix_string;
                oss << step.name << std::setw(table_seperator.length() - step.name.length()) << runtime_string << std::endl;
            }
        }

        oss << std::endl
            << table_seperator << std::endl
            << std::endl;
        std::cout << oss.str();
    }

    // Resets all results
    void reset_results()
    {
        processes.clear();
    }
};
