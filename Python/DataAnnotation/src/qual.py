import pandas as pd


def mainA():
	pd.set_option("display.max_rows", None)
	pd.set_option("display.max_columns", None)

	# Read the CSV file into a DataFrame
	df = pd.read_csv("res/6XWX_bike_rides.csv")

	# Display the first 5 rows
	print(df.head().to_markdown(index=False, numalign="left", stralign="left"))

	# Print the column names and their data types
	print(df.info())

	# Convert `date` to datetime

	df["date"] = pd.to_datetime(df["date"])
	print(df)

	# Filter data by year 2022
	df_2022 = df[df["date"].dt.year == 2022]

	# Compute and print average `group_size` in 2022
	avg_group_size_2022 = df_2022["group_size"].mean()
	print(f"The average group size for rides in 2022 was: {avg_group_size_2022:.2f}")


def mainB():
	# Load the CSV file to check its contents
	file_name = "res/6XWX_bike_rides.csv"
	df = pd.read_csv(file_name)

	# Display the first few rows of the dataframe and the column names
	df.head(), df.columns
	# Convert `date` to datetime

	df["date"] = pd.to_datetime(df["date"], format="%d/%m/%Y", errors="coerce")

	print(df)
	# Filter data by year 2022
	df_2022 = df[df["date"].dt.year == 2022]

	# Compute and print average `group_size` in 2022
	avg_group_size_2022 = df_2022["group_size"].mean()
	print(f"{avg_group_size_2022:.2f}")


if __name__ == "__main__":
	mainA()
	# mainB()
