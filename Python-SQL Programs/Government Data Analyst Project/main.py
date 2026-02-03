#/**------------------------------------------
#     Project: Government Financial Analytics
#     System: VS Code / Python 2025
#     Author: Alejandro Bravo
#  ---------------------------------------------**/

import pandas as pd
import sqlite3
import matplotlib.pyplot as plt
import os
import sys

##################################################################
# Helper: abbreviate_number
# Converts large numbers into readable format (K, M, B)
#
def abbreviate_number(num):
    if num >= 1_000_000_000:
        return f"{num/1_000_000_000:.1f}B"
    elif num >= 1_000_000:
        return f"{num/1_000_000:.1f}M"
    elif num >= 1_000:
        return f"{num/1_000:.1f}K"
    else:
        return f"{num:.0f}"

##################################################################
# show_menu
def show_menu():
    print("\n==============================")
    print(" Government Financial Analytics")
    print("==============================")
    print("1. View summary statistics")
    print("2. View funding pipeline chart")
    print("3. View risk exposure chart")
    print("4. View YoY disbursement trends")
    print("5. Run full analysis")
    print("0. Exit")
#########################################################################
# load_and_clean_data
# Loads CSV, validates schema, applies data quality rules
#
def load_and_clean_data(csv_path):

    required_columns = [
        "Program",
        "Fiscal Year",
        "Approved/Declined Amount",
        "Disbursed/Shipped Amount",
        "Outstanding Exposure Amount",
        "Primary Exporter State Name"
    ]

    df = pd.read_csv(csv_path, low_memory=False)

    missing = [c for c in required_columns if c not in df.columns]
    if missing:
        print("ERROR: Missing required columns:", missing)
        sys.exit(1)

    initial_rows = len(df)

    df = df[required_columns].dropna()

    df.columns = [
        "program",
        "fiscal_year",
        "approved_amount",
        "disbursed_amount",
        "outstanding_amount",
        "state"
    ]

    for col in ["approved_amount", "disbursed_amount", "outstanding_amount"]:
        df[col] = pd.to_numeric(df[col], errors="coerce")

    df = df.dropna()

    # Logical financial consistency
    df = df[
        (df["approved_amount"] >= df["disbursed_amount"]) &
        (df["approved_amount"] >= df["outstanding_amount"])
    ]

    print("Rows removed during cleaning:", initial_rows - len(df))
    print("Final clean row count:", len(df))
    print()

    return df

##################################################################
# print_stats
# Outputs high-level financial metrics
#
def print_stats(dbConn):

    cursor = dbConn.cursor()

    print("General Financial Statistics:")

    cursor.execute("SELECT COUNT(*) FROM transactions;")
    print("  # of records:", f"{cursor.fetchone()[0]:,}")

    cursor.execute("SELECT COUNT(DISTINCT program) FROM transactions;")
    print("  # of programs:", f"{cursor.fetchone()[0]:,}")

    cursor.execute("SELECT COUNT(DISTINCT state) FROM transactions;")
    print("  # of states:", f"{cursor.fetchone()[0]:,}")

    cursor.execute("""
        SELECT 
            SUM(approved_amount),
            SUM(disbursed_amount),
            SUM(outstanding_amount)
        FROM transactions
    """)

    approved, disbursed, outstanding = cursor.fetchone()

    print("  Total approved:", abbreviate_number(approved))
    print("  Total disbursed:", abbreviate_number(disbursed))
    print("  Total outstanding:", abbreviate_number(outstanding))
    print()

##################################################################
# plot_funding_pipeline
#
def plot_funding_pipeline(dbConn, charts_dir):

    df = pd.read_sql("""
        SELECT
            SUM(approved_amount) AS approved,
            SUM(disbursed_amount) AS disbursed,
            SUM(outstanding_amount) AS outstanding
        FROM transactions
    """, dbConn)

    labels = ["Approved", "Disbursed", "Outstanding"]
    values = df.iloc[0].tolist()

    plt.figure(figsize=(7, 5))
    bars = plt.bar(labels, values)
    plt.title("Federal Funding Pipeline")
    plt.ylabel("Amount ($)")

    max_val = max(values)
    for bar, value in zip(bars, values):
        plt.text(
            bar.get_x() + bar.get_width()/2,
            value + max_val * 0.02,
            abbreviate_number(value),
            ha="center"
        )

    plt.ylim(0, max_val * 1.2)
    plt.tight_layout()
    plt.savefig(os.path.join(charts_dir, "funding_pipeline.png"), dpi=200)
    plt.show()

##################################################################
# plot_risk_exposure
#
def plot_risk_exposure(dbConn, charts_dir):

    df = pd.read_sql("""
        SELECT program, SUM(outstanding_amount) AS exposure
        FROM transactions
        GROUP BY program
        ORDER BY exposure DESC
    """, dbConn)

    plt.figure(figsize=(9, 5))
    bars = plt.barh(df["program"], df["exposure"])
    plt.title("Outstanding Risk Exposure by Program")
    plt.xlabel("Exposure ($)")
    plt.gca().invert_yaxis()

    max_val = df["exposure"].max()
    for bar, value in zip(bars, df["exposure"]):
        plt.text(
            value + max_val * 0.01,
            bar.get_y() + bar.get_height()/2,
            abbreviate_number(value),
            va="center"
        )

    plt.xlim(0, max_val * 1.2)
    plt.tight_layout()
    plt.savefig(os.path.join(charts_dir, "risk_exposure.png"), dpi=200)
    plt.show()

##################################################################
# plot_yoy_trends
#
def plot_yoy_trends(dbConn, charts_dir):

    df = pd.read_sql("""
        SELECT fiscal_year, SUM(disbursed_amount) AS total
        FROM transactions
        GROUP BY fiscal_year
        ORDER BY fiscal_year
    """, dbConn)

    df["fiscal_year"] = df["fiscal_year"].astype(int)  # ensure integers
    df["rolling_avg"] = df["total"].rolling(window=3).mean()

    plt.figure(figsize=(8, 5))
    plt.plot(df["fiscal_year"], df["total"], marker="o", label="Actual")
    plt.plot(df["fiscal_year"], df["rolling_avg"], linestyle="--", label="3-Year Avg")

    max_val = df["total"].max()
    for _, row in df.iterrows():
        plt.text(
            row["fiscal_year"],
            row["total"] + max_val * 0.03,
            abbreviate_number(row["total"]),
            ha="center"
        )

    plt.title("Year-over-Year Disbursement Trends")
    plt.xlabel("Fiscal Year")
    plt.ylabel("Disbursed Amount ($)")
    plt.legend()
    plt.xticks(df["fiscal_year"])  # make x-axis integers
    plt.tight_layout()
    plt.savefig(os.path.join(charts_dir, "yoy_trends.png"), dpi=200)
    plt.show()


##################################################################
# main
#
print("** Welcome to Government Financial Analysis App **")
print()

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(BASE_DIR, "governmentData.csv")
db_path = os.path.join(BASE_DIR, "governmentData.db")
charts_dir = os.path.join(BASE_DIR, "charts")
os.makedirs(charts_dir, exist_ok=True)

df = load_and_clean_data(csv_path)

dbConn = sqlite3.connect(db_path)
df.to_sql("transactions", dbConn, if_exists="replace", index=False)

while True:
    show_menu()
    choice = input("Enter choice: ").strip()

    if choice == "1":
        print_stats(dbConn)

    elif choice == "2":
        plot_funding_pipeline(dbConn, charts_dir)

    elif choice == "3":
        plot_risk_exposure(dbConn, charts_dir)

    elif choice == "4":
        plot_yoy_trends(dbConn, charts_dir)

    elif choice == "5":
        print_stats(dbConn)
        plot_funding_pipeline(dbConn, charts_dir)
        plot_risk_exposure(dbConn, charts_dir)
        plot_yoy_trends(dbConn, charts_dir)

    elif choice == "0":
        print("\nExiting application.")
        break

    else:
        print("\nInvalid selection. Please try again.")

dbConn.close()
print("Pipeline completed successfully.")
print("Charts saved to:", charts_dir)


print("Pipeline completed successfully.")
print("Charts saved to:", charts_dir)
