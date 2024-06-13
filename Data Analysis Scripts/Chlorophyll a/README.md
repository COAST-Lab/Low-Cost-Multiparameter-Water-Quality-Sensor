# Chlorophyll a Data Analysis Scripts

This folder contains the data analysis script for the chlorophyll a portion of the sensor. 
Type the .csv address obtained from the low-cost multiparameter sensor into the 'df = pd.read_csv()' of the code. 
The Python code in this folder will filter out the F8 values from the sensor and run this through the calibration curve 
for chlorophyll a values. These chlorophyll a values will be in ug/L and be plotted vs. milliseconds. 
