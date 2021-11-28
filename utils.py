import pandas as pd


def format_cols(df: pd.DataFrame):
    # https://www.geeksforgeeks.org/range-to-a-list-in-python/
    col_nums = [*range(df.shape[1])]
    # df.rename_axis("label", axis="columns", inplace=True)
    df.columns = col_nums
    return col_nums