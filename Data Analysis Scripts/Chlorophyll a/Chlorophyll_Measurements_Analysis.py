import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file, skipping rows with repeated headers
df = pd.read_csv('/Users/jessiewynne/Test_3.csv', skiprows=[1, 2])

# Remove the first occurrence of 'chlorophyll a' measurement
first_chlorophyll_index = df[df['Measurement Type'] == 'chlorophyll a'].index[0]
df = df.drop(first_chlorophyll_index)

# Clean the 'F8 (Raw)' column
df['F8 (Raw)'] = pd.to_numeric(df['F8 (Raw)'], errors='coerce')

# Remove rows with NaN values in the 'F8 (Raw)' column
df_csv = df.dropna(subset=['F8 (Raw)'])

# Filter the DataFrame to get rows where 'Measurement Type' is 'turbidity'
chlorophyll_data = df_csv[df_csv['Measurement Type'] == 'chlorophyll a']

# Extract 'F8 (Raw)' and 'Seconds' values
F8_values = chlorophyll_data['F8 (Raw)']
seconds_values = chlorophyll_data['Seconds']

# Solve for x using the equation y = 0.7231x + 9.0639
x_values_csv = (F8_values - 9.0639) / 0.7231

# Plot
plt.plot(seconds_values, x_values_csv, marker='o', linestyle='-')
plt.xlabel('Seconds')
plt.ylabel('ug/L')
plt.title('Chlorophyll a Measurements vs. Seconds')
plt.grid(True)
plt.show()
