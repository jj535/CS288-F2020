from xml.dom.minidom import parse
import sys
import pymysql

def get_text(e):
    lst=[]
    if e.nodeType in (3,4):
        lst.append(e.data)
    else:
        for y in e.childNodes:
            lst+=get_text(y)
    return lst

def compose_q(fn, dic):
    pr=dic['Price (Intraday)']
    pr=float(pr)
    chng=float(dic['Change'].replace(',',''))
    
    pchng=float(dic['% Change'].replace('%','').replace(',',''))
    vol=float(dic['Volume'].replace('M','').replace(',',''))
    avgvol=float(dic['Avg Vol (3 month)'].replace('M','').replace(',',''))

    mcap=dic['Market Cap']
    if mcap[-1]=='B':
        mcap=float(mcap[:-1])
    else:
        mcap=1000*float(mcap[:-1])
    PER=dic['PE Ratio (TTM)'].replace(',','')
    if PER == 'N/A':
        PER=float(0)
    else:
        PER=float(PER)
    s="insert into " + fn + " (Symbol, Name, Price, nChange, pChange, Volume, AvgVolume, MarketCap, PERatio) " + "values (" + '\'' + dic['Symbol'] + '\'' + ', '+'\''+ dic['Name'].replace('\'','')+'\'' + ', ' + str(pr) + ', '+ str(chng) + ', '+ str(pchng) + ', '+  str(vol)  + ', '+ str(avgvol) + ', ' + str(mcap) + ', '+ str(PER) + ");"

   # print(s)
    return s

def xhtml_to_dict(xfn):
    dom=parse(xfn)
    elms=dom.getElementsByTagName('tr')
    hdr=elms[0]
    del elms[0]
    ll=[]
    for e in elms:
        ll.append(get_text(e))
    #print(ll)
    hdr_txt=get_text(hdr)
    hdr_txt=hdr_txt[:9]
    #print(hdr_txt)
    rtn=[]
    for vals in ll:
        d=dict(map(lambda k,v: (k,v), hdr_txt, vals))
        rtn.append(d)
    return rtn

#fn is file name and dd is data dictionary
def insert_to_db(fn, dd):
    db=pymysql.connect('localhost', 'root', 'password', 'stock_market')
    cursor=db.cursor()
    
    #erase preexisting table if any
    s="DROP TABLE IF EXISTS " + fn + ";"
    cursor.execute(s)
    
    #create new table, made headers, etc
    s="CREATE TABLE " + fn + " (Symbol varchar(10), Name varchar(80), Price float, nChange float, pChange float, Volume float, AvgVolume float, MarketCap float, PERatio float);"
    cursor.execute(s)

    #insert all data
    l_q=list(map(lambda x: compose_q(fn,x), dd))
    for q in l_q:
        cursor.execute(q)

    #show all table 
    s='select * from ' + fn
    result = cursor.execute(s)

    #commit to db, close all
    cursor.close()
    db.commit()
    db.close()

def print_table(dic, fn):
    print(str(len(dic)) + " rows in the table " + fn)
    ks=dic[0].keys()
    for k in ks:
        print ("%-*s" % (17,k), end = ' ')
    print()
    for row in dic:
        for k in ks:
            if len(row[k]) >=17:
                rr=row[k][:17]
            else:
                rr=row[k]
            print ("%-*s" % (17, rr) , end = ' ')
        print()


def main():
    xhtml_fn=sys.argv[1]
    data_dict = xhtml_to_dict(xhtml_fn)
    fn=xhtml_fn.replace('.xhtml', '')
    print_table(data_dict, fn)
    insert_to_db(fn, data_dict)


if __name__ == "__main__":
    main()
