#!/usr/bin/perl

use strict;
use warnings;

# List of test cases
my @test_cases = ( "sample", "input_1", "input_2", "input_3", "input_4", "input_5" );

# Executable name
my $target = "./Lab1";

# Create a log folder if it doesn't exist
mkdir("log") unless -d "log";

# Initialize an array to store information for each test case
my @test_case_info;

# Loop through each test case
foreach my $test_case (@test_cases) {
    my $input_file = "testcase/$test_case.dat";
    my $output_file = "testcase/$test_case.out";

    # Define the log file path for the program's output
    my $log_file = "log/$test_case.log";

    # Define the verifier log file path
    my $verifier_log_file = "log/$test_case"."_verifier.log";

    # Define the timing log file path
    my $timing_log_file = "log/$test_case"."_timing.log";

    # Measure the execution time of the $target command and capture it in the timing log
    my $start_time = time();
    system("$target $input_file $output_file > $log_file 2>> $timing_log_file");
    my $end_time = time();

    my $execution_time = $end_time - $start_time;

    # Verify the solution and capture the verifier output in the verifier log file
    system("./verifier/SolutionChecker $input_file $output_file >> $verifier_log_file");

    # Write the execution time to the timing log file
    open my $timing_log, '>>', $timing_log_file;
    print $timing_log "Execution Time: $execution_time seconds\n";
    close $timing_log;

    # Store information for the test case
    push @test_case_info, {
        test_case => $test_case,
        log_file => $log_file,
        verifier_log_file => $verifier_log_file,
        timing_log_file => $timing_log_file,
        execution_time => $execution_time,
    };

    print "Test case $test_case completed. Logs stored in $log_file, $verifier_log_file, and $timing_log_file\n";
}

# Generate a report
open my $report, '>', 'report.txt';
print $report "Test Case Report:\n\n";

foreach my $info (@test_case_info) {
    print $report "Test Case: $info->{test_case}\n";
    print $report "Execution Time: $info->{execution_time} seconds\n";
    print $report "Log File: $info->{log_file}\n";
    print $report "Verifier Log File: $info->{verifier_log_file}\n";
    print $report "Timing Log File: $info->{timing_log_file}\n\n";
}

close $report;

print "Report generated and saved as 'report.txt'\n";
