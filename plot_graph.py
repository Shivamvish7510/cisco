import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import pandas as pd
import numpy as np

# Load data
df = pd.read_csv("sorting_result.csv")


# Sort the data by the "Size" column
df = df.sort_values(by='Size')

# Save the sorted data to a new CSV file
df.to_csv('sorted_file.csv', index=False)

# Plot comparisons
plt.figure(figsize=(10,6))
plt.plot(df["Size"], df["Insertion"], label="Insertion Sort", marker='o')
plt.plot(df["Size"], df["Merge"], label="Merge Sort", marker='s')
plt.plot(df["Size"], df["Heap"], label="Heap Sort", marker='^')
plt.plot(df["Size"], df["Quick"], label="Quick Sort", marker='d')



# Labels and legend
plt.xlabel("Input Size (n)")
plt.ylabel("Average Comparisons")
plt.title("Sorting Algorithm Comparisons")
plt.legend()
plt.grid()

# Set the format of the y-axis
plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda x, p: format(int(x), ',')))

# Set the format of the x-axis
plt.gca().xaxis.set_major_formatter(ticker.FuncFormatter(lambda x, p: format(int(x), ',')))

plt.show()
