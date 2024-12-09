import pandas as pd
import matplotlib.pyplot as plt

csv_file = "sorting_results.csv"
data = pd.read_csv(csv_file)

plt.figure(figsize=(10, 6))
plt.plot(data["Array Size"], data["Selection Sort"], label="Selection Sort", marker="o")
plt.plot(data["Array Size"], data["Insertion Sort"], label="Insertion Sort", marker="s")
plt.plot(data["Array Size"], data["Binary Insertion Sort"], label="Binary Insertion Sort", marker="^")
plt.plot(data["Array Size"], data["Merge Sort"], label="Merge Sort", marker="d")

plt.title("Comparison of Sorting Algorithm Execution Times", fontsize=14)
plt.xlabel("Array Size", fontsize=12)
plt.ylabel("Execution Time (seconds)", fontsize=12)
plt.grid(True, linestyle="--", alpha=0.6)
plt.legend(fontsize=10)
plt.tight_layout()

plt.savefig("sorting_comparison_graph.png")
plt.show()
