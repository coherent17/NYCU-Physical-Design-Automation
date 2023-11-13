#!/usr/bin/perl

use strict;
use warnings;

# Function to generate a random number between min and max (inclusive)
sub generate_random_number {
    my ($min, $max) = @_;
    return int($min + rand($max - $min + 1));
}

# Prompt user for the number of blocks
print "Enter the number of blocks: ";
my $num_blocks = <STDIN>;
chomp($num_blocks);

# Validate input
if ($num_blocks !~ /^\d+$/ || $num_blocks <= 0) {
    die "Invalid input. Please enter a positive integer for the number of blocks.\n";
}

# Open output file for writing
open my $output_file, '>', 'output.txt' or die "Could not open output.txt: $!\n";

# Print the header
print $output_file "0.5 $num_blocks\n";

# Generate block information
for my $i (1..$num_blocks) {
    my $width = generate_random_number(1, 100);
    my $height = generate_random_number(1, 100);

    # Print block information to the output file
    print $output_file "b$i $width $height\n";
}

# Close the output file
close $output_file;

print "Output file 'output.txt' generated successfully.\n";
