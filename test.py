def do():
    with open("/tmp/ubnt_burnin_log", "rb") as file:
         data = file.read(8)

    print(data)
    
    with open("/tmp/out.txt", "w") as f:
        f.write(" ".join(map(str,data)))
        f.write("\n")

if __name__ == "__main__":
    do()