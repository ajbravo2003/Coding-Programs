import streamlit as st
import pandas as pd
import sqlite3

st.set_page_config(page_title="Government Financial Dashboard", layout="wide")

st.title("Government Financial Data Dashboard")

# Load data
df = pd.read_csv("governmentData.csv", low_memory=False)

df = df[[
    "Program",
    "Fiscal Year",
    "Approved/Declined Amount",
    "Disbursed/Shipped Amount",
    "Outstanding Exposure Amount",
    "Primary Exporter State Name"
]].dropna()

df.columns = [
    "program",
    "fiscal_year",
    "approved",
    "disbursed",
    "exposure",
    "state"
]

# ------------------------
# Sidebar filters
# ------------------------
st.sidebar.header("Filters")

programs = st.sidebar.multiselect(
    "Select Program",
    sorted(df["program"].unique())
)

states = st.sidebar.multiselect(
    "Select State",
    sorted(df["state"].unique())
)

years = st.sidebar.slider(
    "Fiscal Year Range",
    int(df["fiscal_year"].min()),
    int(df["fiscal_year"].max()),
    (int(df["fiscal_year"].min()), int(df["fiscal_year"].max()))
)

# Apply filters
filtered_df = df.copy()

if programs:
    filtered_df = filtered_df[filtered_df["program"].isin(programs)]

if states:
    filtered_df = filtered_df[filtered_df["state"].isin(states)]

filtered_df = filtered_df[
    (filtered_df["fiscal_year"] >= years[0]) &
    (filtered_df["fiscal_year"] <= years[1])
]

# ------------------------
# KPIs
# ------------------------
st.subheader("Key Metrics")

col1, col2, col3 = st.columns(3)

col1.metric("Total Approved", f"${filtered_df['approved'].sum():,.0f}")
col2.metric("Total Disbursed", f"${filtered_df['disbursed'].sum():,.0f}")
col3.metric("Total Exposure", f"${filtered_df['exposure'].sum():,.0f}")

# ------------------------
# Charts
# ------------------------
st.subheader("Funding Breakdown by Program")

program_summary = (
    filtered_df
    .groupby("program")[["approved", "disbursed", "exposure"]]
    .sum()
    .sort_values("disbursed", ascending=False)
)

st.bar_chart(program_summary)
