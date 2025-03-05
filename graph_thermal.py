'''import matplotlib.pyplot as plt
import pandas as pd
#import seaborn as sns

data = pd.read_csv("C:\\Users\\Bhavana\\Desktop\\sensors_data.csv")


plt.figure(figsize=(15, 10))
#sns.set_style("whitegrid")

for sensor in ['Thermoelectric', 'Thermoresistive', 'ThermoOptical', 'ThermoAcoustic']:
    plt.plot(data['Time'], data[sensor], label=sensor, alpha=0.6)

plt.plot(data['Time'], data['Average'], 'k-', label='Average', linewidth=2)
plt.axhline(y=35, color='r', linestyle='--', label='Fan Threshold')
plt.axhline(y=6, color='b', linestyle='--', label='Heater Threshold')

plt.xlabel('Time (s)')
plt.ylabel('Temperature (°C)')
plt.title('Temperature Sensor Readings')
plt.legend()
plt.savefig('temperature_analysis.png')
plt.close()'''

'''import pandas as pd
import matplotlib.pyplot as plt
#import seaborn as sns

# Set the style for the plot
#plt.style.use('seaborn')
#sns.set_palette("husl")

# Read the CSV file
df = pd.read_csv("C:\\Users\\Bhavana\\Desktop\\test.csv")

# Create the plot
plt.figure(figsize=(12, 6))

# Plot each sensor's data
plt.plot(df['Time'], df['Thermoelectric'], label='Thermoelectric', linewidth=2)
plt.plot(df['Time'], df['RTD'], label='RTD', linewidth=2)
plt.plot(df['Time'], df['Thermistor'], label='Thermistor', linewidth=2)
plt.plot(df['Time'], df['Thermooptical'], label='Thermooptical', linewidth=2)
plt.plot(df['Time'], df['Thermoacoustic'], label='Thermoacoustic', linewidth=2)

# Add threshold lines
plt.axhline(y=35.0, color='r', linestyle='--', label='Cooling Threshold')
plt.axhline(y=6.0, color='b', linestyle='--', label='Heating Threshold')

# Customize the plot
plt.title('Temperature Readings from Different Sensors Over Time', pad=20)
plt.xlabel('Time (seconds)')
plt.ylabel('Temperature (°C)')
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.grid(True, linestyle='--', alpha=0.7)

# Add some padding to the right for the legend
plt.tight_layout()

# Save the plot
#plt.savefig('temperature_plot.png', bbox_inches='tight', dpi=300)
plt.show()'''

import pandas as pd
import matplotlib.pyplot as plt


# Read the CSV file
df = pd.read_csv("C:\\Users\\Bhavana\\Desktop\\test1.csv")

# Create a single large plot
plt.figure(figsize=(15, 8))

# Plot individual sensor readings with reduced alpha for clarity
plt.plot(df['Time'], df['Thermoelectric'], label='Thermoelectric', linewidth=1, alpha=0.4)
plt.plot(df['Time'], df['RTD'], label='RTD', linewidth=1, alpha=0.4)
plt.plot(df['Time'], df['Thermistor'], label='Thermistor', linewidth=1, alpha=0.4)
plt.plot(df['Time'], df['Thermooptical'], label='Thermooptical', linewidth=1, alpha=0.4)
plt.plot(df['Time'], df['Thermoacoustic'], label='Thermoacoustic', linewidth=1, alpha=0.4)

# Plot average temperature with greater prominence
plt.plot(df['Time'], df['Average'], label='Average', color='black', linewidth=2.5)

# Add threshold lines
plt.axhline(y=35.0, color='red', linestyle='--', label='Cooling Threshold (35°C)', alpha=0.8)
plt.axhline(y=6.0, color='blue', linestyle='--', label='Heating Threshold (6°C)', alpha=0.8)

# Add fan and heater status indicators
fan_on = df[df['Fan_Status'] == 1]
heater_on = df[df['Heater_Status'] == 1]

if not fan_on.empty:
    plt.scatter(fan_on['Time'], fan_on['Average'], color='red', label='Fan ON', 
               marker='^', alpha=0.5, s=50)
if not heater_on.empty:
    plt.scatter(heater_on['Time'], heater_on['Average'], color='blue', label='Heater ON', 
               marker='v', alpha=0.5, s=50)

# Customize the plot
plt.title('Temperature Monitoring System Overview', pad=20, fontsize=14)
plt.xlabel('Time (seconds)', fontsize=12)
plt.ylabel('Temperature (°C)', fontsize=12)

# Improve legend
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', fontsize=10)
plt.grid(True, linestyle='--', alpha=0.7)
# Adjust layout
plt.tight_layout()

# Save the plot
#plt.savefig('temperature_plot.png', bbox_inches='tight', dpi=300)
plt.show()