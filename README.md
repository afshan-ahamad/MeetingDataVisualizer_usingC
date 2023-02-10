# MeetingDataVisualizer_usingC

## Introduction
Due to the social distancing and travel restrictions all around the world, people have moved most of the work to virtual environments. Due to this, the usage of meeting tools has exponentially increased so as the data gathered through such tools. The objective of this project is to analyze such data files and visually represent the data as per the requirement of user.

![File](https://user-images.githubusercontent.com/104277153/218191355-3011155d-c8d5-403b-83be-e37a8687d443.JPG)

Figure shows the expected output from the program. People with most number of meetings are displayed as a horizontal bar chart
Fig 1 shows the expected output from the program concerning the maximum number of meetings.
There are different control and input arguments for the program. According to the arguments, the program should be able to change its behaviour and result in the expected output.

## Program output

### Control arguments for the program
- File name/ File Names
The program should be able to accept any number of file names in any order. Input files should be CSV files. Also the file names will not start with ‘-’. eg: -file.csv

- Number of rows in the chart
The argument specifies the number of rows in the bar chart. It should be given as −l 10 where 10 is the limit. It can be any positive integer. A number should always follow the −l argument. The pair can be in any place of the arguments list.
- Scaled option
When − − scaled argument is given, the first row of the graph should fully occupy the max print width. Any other row should scale to be matched with first row scale factor.

![File1](https://user-images.githubusercontent.com/104277153/218191943-24de68df-4df3-4e37-a56e-e9ef29323ee7.JPG)

This figure shows the expected output from the program. 5 people with most number of meetings are displayed as a horizontal bar chart. The bar for the greatest value expands trough out the print area and others are proportional to that.

- Meetings/participants/duration Representation
The program can analyse three different parameters, No. of Meetings, No. of Participants and
Duration. If the output should list meetings, the −m should be given. If the output should list
participant counts, the −p should be given. If the output should list time duration, the −t should be
given.

![File2](https://user-images.githubusercontent.com/104277153/218192281-15b04212-5113-4022-81f8-52613a416713.JPG)

The expected output from the program. People with maximum meeting duration in minutes are displayed as a horizontal bar chart.

### Default options
The program must take at least one file name to work. All other arguments are optional. If not given, the program will work as non-scaled, will output counts for meeting and limit the output rows to 10.

