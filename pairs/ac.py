def isOk(x,y,data):
    for datax,datay in data:
        if datax != x and datay != x and datax!=y and datay!=y:
            return  False   
    return True
        
        
        
def findCommonPair(data):
    for i in data[0]:      
        if isOk(i,-1,data):
            return 'yes'+str(i)+str(-1)
        
        for x,y in data[1:]:            
            if i!=x or i!=y:
                for j in (x,y): 
                    print(j,'::',isOk(i,j,data))
                    if isOk(i,j,data):                        
                        return 'yes'+str(i)+str(j)
        
    
    return 'NO'



data=[[4,2],[2,4],[4,7],[7,4],[4,0],[4,9],[4,2]]
print(findCommonElement(data))
