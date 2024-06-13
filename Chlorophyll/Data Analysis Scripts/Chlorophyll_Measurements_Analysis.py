import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv('/Users/jessiewynne/turb_dock_test_4_15_24_no_DI.csv')

# Clean the 'F8 (Raw)' column
df['F8 (Raw)'] = pd.to_numeric(df['F8 (Raw)'], errors='coerce')

# Remove rows with NaN values in the 'F8 (Raw)' column
df_csv = df.dropna(subset=['F8 (Raw)'])

# Filter the DataFrame to get rows where 'Measurement Type' is 'turbidity'
chlorophyll_data = df_csv[df_csv['Measurement Type'] == 'chlorophyll a']

# Extract 'F8 (Raw)' and 'Milliseconds' values
F8_values = chlorophyll_data['F8 (Raw)']
milliseconds_values = chlorophyll_data['Milliseconds']

# Solve for x using the equation y = 0.7231x + 9.0639
x_values_csv = (F8_values - 9.0639) / 0.7231

# Plot
plt.plot(milliseconds_values, x_values_csv, marker='o', linestyle='-')
plt.xlabel('Milliseconds')
plt.ylabel('ug/L')
plt.title('Chlorophyll a Measurements vs. Milliseconds')
plt.grid(True)
plt.show()