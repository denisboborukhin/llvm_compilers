import matplotlib.pyplot as plt
from collections import defaultdict

def parse_data(file_path):
    result = defaultdict(int)
    with open(file_path, 'r') as file:
        for line in file.readlines():
            if line not in result:
                result[line] = 1
            else:
                result[line] += 1 
    return {k: v for k, v in sorted(result.items(), key=lambda item: item[1], reverse=True)}

if __name__ == "__main__":
    data = parse_data("../trace/app.trace")

    plt.figure(figsize=(18, 8))
    plt.bar(data.keys(), data.values(), color='c')
  
    plt.xlabel('combinations')
    plt.ylabel('executions')
    plt.title('most common combinations')
  
    plt.savefig("../trace/common_combinations.png", format="png", bbox_inches="tight")
 