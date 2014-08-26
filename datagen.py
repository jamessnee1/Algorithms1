#! /usr/bin/env python
"""
A simple Python script for generating data for the assignment.
- David Shaw 2014
"""

import optparse, random

try:
	set
except NameError:
	from sets import Set as set

# command line arguments & helpful messages
def main():
	parser = optparse.OptionParser()
	parser.add_option("--command", "-c", action="store",
		default="IDS",
		help="type of data to generate -"
		"I,D,S, or a string to randomly choose from "
		"(\"IDS\", \"IISSS\", etc.)"
		)
	parser.add_option("--amount", "-n", type="int", default=100,
		help="number of commands to generate")
	parser.add_option("--range", "-r", type=int, default=100,
		help="upper bound on range of values "
		     " (max = 10000000, default = 100)")
	parser.add_option("--seed", "-x", type=int,
		help="random seed")
	parser.add_option("--unique", "-u", action="store_true",
		help="generate unique values (no repeats),"
		" not too useful with mixed commands")

	options, arguments = parser.parse_args()

	if options.seed:
		random.seed(options.seed)

	options.range = min(options.range, 10000000)

	cmd = options.command

	if options.unique:
		cmd_unique(options.amount, options.range, cmd)
	else:
		cmd_repeat(options.amount, options.range, cmd)

def cmd_unique(n, maxval, cmd):
	samples = set()
	n = min(n, maxval)
	unique_list = random.sample(range(maxval), n)
	for val in unique_list:
		print "%c %d" % (random.choice(cmd),val)
	
def cmd_repeat(n, maxval, cmd):
	for i in range(n):
		print "%c %d" % (random.choice(cmd),random.randrange(maxval))

if __name__ == "__main__":
	main()



