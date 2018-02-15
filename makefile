obj=daytimetcpcli.o
daytimetcpcli:$(obj) unp.h
gcc -o daytimetcpcli daytimetcpcli.o unp.h
@echo "make complete..."
daytimetcpcli.o:
clean:
rm daytimetcpcli $(obj)
@echo "dyatimetcpcli , &(obj) files are removed..."
