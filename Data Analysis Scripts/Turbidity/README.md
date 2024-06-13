# Turbidity Data Analysis Script

This folder contains the data analysis script for the turbidity portion of the sensor. Type the .csv address obtained from the low-cost multiparameter sensor into the 'df = pd.read_csv()' of the code. The Python code in this folder will filter out the NIR values from the sensor and run this through the calibration curve for turbidity values. These turbidity values will be in FNU and be plotted vs. milliseconds.
