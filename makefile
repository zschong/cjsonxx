CC := g++
CFLAGS := -Wall -g -Iinclude
LDFLAGS := -lcjson
CPP_SRC := cjsonxx.cc cjsonxx_object.cc cjsonxx_array.cc cjsonxx_base.cc

all: cjsonxx.exe

# 调用 `cJSON_CreateNumber(double value, int pricision)` 无精度控制接口
jsonxx.exe: $(CPP_SRC)
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS) -DCJSONXX_TEST

# 调用 `cJSON_CreateNumber(double value)` 无精度控制接口, cJSON库原始接口无精度控制
jsonxxorg.exe: $(CPP_SRC)
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS) -DCJSONXX_TEST -DCJSON_ORIGIN


clean:
	rm *.exe -rf
