import pandas as pd
import matplotlib.pyplot as plt

# Additional FTU values from another source
# Additional chlorophyll values from another source

# additional_chl_values = {
#      ' Approx Time': ['11:30', '11:45', '12:00', '12:15', '12:30', '12:45', '13:00', '13:15', '13:30', '13:45'],
#     'ug/L': [0.93, 0.69, 0.85, 0.73, 0.82, 0.76, 1.54, 1.07, 1.60, 1.24]
# } #4/23 insode


# additional_chl_values = {
#       ' Approx Time': ['8:45', '9:00','9:15','9:30','9:45', '10:00','10:15', '10:30','10:45', '11:00'],
#      'ug/L': [1.00, 1.39, 2.03, 1.81, 1.46, 1.67, 1.18, 1.21, 0.95, 0.87]
#  } #4/23 afternoon outside

additional_chl_values = {
    ' Approx Time': ['10:15', '10:30','10:45','11:00','11:15', '11:30','11:45', '12:00','12:15', '12:30','12:45','13:00','13:15', '13:30','13:45','14:00'],
    'ug/L': [3.12, 3.92, 4.89, 5.14, 5.06, 7.15,4.58, 3.36, 3.65, 4.54, 4.26, 5.16, 9.65, 4.98, 4.43, 6.97]
} # 4/15 data morning outside 

# Read the CSV file
df = pd.read_csv('/Users/jessiewynne/chl_dock_test_4_15_24 .csv')

# Clean the 'NIR (Raw)' column
df['F8 (Raw)'] = pd.to_numeric(df['F8 (Raw)'], errors='coerce')

# Remove rows with NaN values in the 'NIR (Raw)' column
df_csv = df.dropna(subset=['F8 (Raw)'])

# Group by 'Approx Time' and calculate the average of 'NIR (Raw)' for each group
averages_csv = df_csv.groupby(' Approx Time')['F8 (Raw)'].mean()

# Solve for x using the equation y = 76.3208x + 1578.2578
x_values_csv = ((averages_csv - 9.0639) / 0.7231)

# Create a DataFrame for the additional FTU values
df_f8 = pd.DataFrame(additional_chl_values)

# Merge the CSV and additional FTU DataFrames on 'Approx Time' with specified suffixes
merged_df = pd.merge(df_f8, pd.DataFrame(averages_csv), left_on=' Approx Time', right_index=True, how='inner', suffixes=('_x', '_y'))

# Reset the index of x_values_csv
x_values_csv = x_values_csv.reset_index(drop=True)

# Calculate the absolute differences in FTU values per Approx Time between the .csv file values and the imported FTU values
merged_df['F8_diff'] = abs(df_f8['ug/L'] - x_values_csv)

# Calculate the average error
average_error = merged_df['F8_diff'].mean()

# Calculate the normalized values

normalized_x_values = x_values_csv - average_error

# Filter out the 'DI' row
df_f8 = df_f8[df_f8[' Approx Time'] != 'DI']

# # Remove the last two 'Approx Time' values to match the dimensions
# df_f8 = df_f8[:-7]

# Plot the data
plt.figure(figsize=(12, 6))
plt.plot(averages_csv.index, x_values_csv, 'o', label='Sensor Data', alpha=0.7)
plt.scatter(df_f8[' Approx Time'], df_f8['ug/L'], color='red', label='CORMP Data', alpha=0.7)
plt.text(0.2, 0.6, f'Average Error: {average_error:.2f} F8', transform=plt.gca().transAxes, color='green')
plt.xlabel('Approx Time')
plt.ylabel('ug/L')
plt.title('Chlorophyll CORMP vs Sensor Values 4/25/24 Outdoor')
plt.legend()
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()

# # Create a new figure for the normalized graph
# plt.figure(figsize=(12, 6))
# plt.plot(df_f8[' Approx Time'], normalized_x_values[:9], 'o', label='Normalized Sensor Chlorophyll Values', alpha=0.7)
# plt.scatter(df_f8[' Approx Time'], df_f8['ug/L'], label='CORMP Chlorophyll Values', color='red', alpha=0.7)
# plt.xlabel('Approx Time')
# plt.ylabel('Chlorophyll Values')
# plt.title('Normalized Sensor Chlorophyll Values vs. CORMP Turbidity Values 4/15/24 Outdoor')
# plt.legend()
# plt.grid(True)
# plt.xticks(rotation=45)
# plt.tight_layout()
# plt.show()
