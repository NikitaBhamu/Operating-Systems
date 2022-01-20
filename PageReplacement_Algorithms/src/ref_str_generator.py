import random

def input_generator(filename,n, page_frame,page_start,page_end):
  filee = open(filename,"a")
  filee.write(str(n)+" "+str(page_frame))
  filee.write("\n")
  lst = []
  for i in range(n):
    lst.append(str(random.randint(page_start, page_end))+" ")
  filee.writelines(lst)
  filee.write("\n")
  filee.close()


file = open("input.txt","w");
file.close()
sr = "input.txt"
size1 = input("Enter size of the reference string : ")
size2 = input("Enter no. of page frames : ")
page_start = input("Page no. starts from : ")
page_end = input("Page no. ends at : ")
input_generator(sr,int(size1),int(size2), int(page_start), int(page_end))
