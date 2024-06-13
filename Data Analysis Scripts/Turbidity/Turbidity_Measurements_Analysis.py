import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv('/Users/jessiewynne/turb_dock_test_4_15_24_no_DI.csv')

# Clean the 'NIR (Raw)' column
df['NIR (Raw)'] = pd.to_numeric(df['NIR (Raw)'], errors='coerce')

# Remove rows with NaN values in the 'NIR (Raw)' column
df_csv = df.dropna(subset=['NIR (Raw)'])

# Filter the DataFrame to get rows where 'Measurement Type' is 'turbidity'
turbidity_data = df_csv[df_csv['Measurement Type'] == 'turbidity']

# Extract 'NIR (Raw)' and 'Milliseconds' values
nir_values = turbidity_data['NIR (Raw)']
milliseconds_values = turbidity_data['Milliseconds']

# Solve for x using the equation y = 79.5485x + 1507.2419
x_values_csv = (nir_values - 1507.2419) / 79.5485

# Plot
plt.plot(milliseconds_values, x_values_csv, marker='o', linestyle='-')
plt.xlabel('Milliseconds')
plt.ylabel('FNU')
plt.title('Turbidity Measurements vs. Milliseconds')
plt.grid(True)
plt.show()
