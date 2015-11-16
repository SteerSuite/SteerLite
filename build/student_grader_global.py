###############################
# Computer Geraphic Course F15
# Grading Script
# @Author VaHid aZiZi
###############################

import json
import gspread
from oauth2client.client import SignedJwtAssertionCredentials
import subprocess
import sys
from termcolor import colored
import re
import os.path


def main():
	if len(sys.argv) < 3:
        	sys.exit('Please follow below foramt:\npython student_grader_global.py YOUR_JSON_FILE GROUP_NUMBER')

	try:
		json_key = json.load(open(str(sys.argv[1])))
		scope = ['https://spreadsheets.google.com/feeds']

		credentials = SignedJwtAssertionCredentials(json_key['client_email'], json_key['private_key'].encode(), scope)

		gc = gspread.authorize(credentials)

		wks = gc.open_by_url('https://docs.google.com/spreadsheets/d/1zYIBd7ZiBIZRLrxm1NLtZ6n_ivnWX-JDsENuRlcOoHI/edit?usp=sharing').sheet1
	except Exception as e:
		print colored(e, 'red')

	testCases= ['plane_engress','plane_ingress','crowd_crossing', 'office-complex', 'hallway-four-way-rounded-roundabout']
	finalRes = []

	try:
		for testcase in testCases:
			if os.path.exists(testcase + '-' + str(sys.argv[2]) + '.rec'):
				print colored(testcase, 'red')
				result = subprocess.Popen('./steerbench ' + testcase + '-' + str(sys.argv[2]) + '.rec -details -technique composite02', shell=True, stdout=subprocess.PIPE).stdout.read()
				print(result)

				final_score= re.findall(r'\d+\.?\d*',str(result))
				print colored( final_score[-1], 'cyan')
				finalRes.append(final_score[-1])
			else:
				print colored(testcase, 'red')
				print colored(testcase + '-' + str(sys.argv[2]) + '.rec is not available', 'yellow')
				finalRes.append(0)
				print colored(0,'cyan')
	except Exception as e:
		print colored(e, 'red')

	print colored( '\nFinal Score for testcases:', 'green' )
	for testcase, res in map(None,testCases,finalRes):
		print colored( testcase + ' ===> ' + str(res), 'green' )

	groupList = wks.col_values(1)

	if sys.argv[2] in groupList:
		print colored('Record for this group is available, update...', 'blue')
		mode = 0
	else:
		print colored('Record for this group is not available, insert...', 'blue')
		mode = 1

	values = []
	values.append(sys.argv[2])
	for i in range(len(finalRes)):
		values.append(finalRes[i])

	if mode == 1:
		if len(groupList) > 1:
			wks.insert_row(values,len(groupList)+1)
		else:
		 	wks.insert_row(values, 2)
		print colored('Your Records Are Inserted.','blue', 'on_red')
	elif mode == 0:
		cur_row = groupList.index(sys.argv[2])
		for i in range(len(finalRes)):
			wks.update_cell(cur_row+1, 2+i, finalRes[i])
		print colored('Your Records Are Update.','blue', 'on_red')


if __name__ == '__main__':
	main()
