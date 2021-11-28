import pandas as pd
import math
from tqdm import tqdm


def feature_search(df:pd.DataFrame, cols):
    curr_features = {0}
    print(cols)
    for i in cols:
        print(f'level {i}:')
        this_level_feature = 0
        max_acc = 0

        for k in cols:
            if k not in curr_features:
                print(f'\tConsidering adding feature {k}')
                accuracy = cross_val(df, curr_features, k)
                if accuracy > max_acc:
                    max_acc = accuracy 
                    this_level_feature = k
                    

        curr_features.add(this_level_feature)
        print(f'On level {i}, added feature {this_level_feature} to the current set')
    
    print('curr_features: ', curr_features)


def cross_val(in_df:pd.DataFrame, current_set, feature_to_add):
    new_set = current_set.copy()
    new_set.add(feature_to_add)
    print(new_set)
    df = in_df[new_set]
    correct_class_count = 0

    for i in tqdm(range(df.shape[0])):
        curr_obj = df.loc[i][1:]
        curr_label = df.loc[i].iloc[0]
        

        nearest_neighbor_dist = float('inf')
        nearest_neighbor_location = float('inf')
        

        for k in range(df.shape[0]):
            if k != i:
                dist = math.sqrt(((curr_obj - df.iloc[k][1:]) ** 2).sum())
                if dist < nearest_neighbor_dist:
                    nearest_neighbor_dist = dist
                    nearest_neighbor_location = k
                    nearest_neighbor_label = df.loc[k].iloc[0]

        if curr_label == nearest_neighbor_label:
            correct_class_count += 1
    print(correct_class_count)
    return correct_class_count / df.shape[0]
# in the slides: 1 is down, 2 is right -> 0 is down, 2 is right in python
