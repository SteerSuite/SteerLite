###############################
# Computer Geraphic Course F15
# Grading Script
# @Author VaHid aZiZi
###############################


import subprocess
import sys
from termcolor import colored
import os.path
import re


def main():
	if len(sys.argv) < 2:
        	sys.exit('Please follow below foramt:\npython student_grader_local.py GROUP_NUMBER')

	testCases= ['plane_engress','plane_ingress','crowd_crossing', 'office-complex', 'hallway-four-way-rounded-roundabout']
	finalRes = []

	try:
		for testcase in testCases:
			if os.path.exists(testcase + '-' + str(sys.argv[1]) + '.rec'):
				print colored(testcase, 'red')
				result = subprocess.Popen('./steerbench ' + testcase + '-' + str(sys.argv[1]) + '.rec -details -technique composite02', shell=True, stdout=subprocess.PIPE).stdout.read()
				print(result)

				final_score= re.findall(r'\d+\.?\d*',str(result))
				print colored( final_score[-1], 'cyan')
				finalRes.append(final_score[-1])
			else:
				print colored(testcase, 'red')
				print colored(testcase + '-' + str(sys.argv[1]) + '.rec is not available', 'yellow')
				finalRes.append(0)
				print colored(0,'cyan')
	except Exception as e:
		print colored(e, 'red')

	print colored( '\nFinal Score for testcases:', 'green' )
	for testcase, res in map(None,testCases,finalRes):
		print colored( testcase + ' ===> ' + str(res), 'green' )

if __name__ == '__main__':
	main()
