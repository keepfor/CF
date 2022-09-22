def main():
    s = input()
    while s:
        s = s.replace('[', '{')
        s = s.replace(']', '}')
        print(s)
        try:
            s = input()
        except:
            break
main()
