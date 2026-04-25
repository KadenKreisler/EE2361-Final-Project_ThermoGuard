#ifndef TEMP_LIB_FPROJECT_H
#define TEMP_LIB_FPROJECT_H

#ifdef __cplusplus
extern "C" {
#endif
    
    void low();
    void release();
    int temp_reset(void);
    void write_0();
    void write_1();
    int read_bit();
    int read_byte();
    void write_byte(char byte_1);

    void temp_init(void);
    void temp_update(void);     // non-blocking
    double get_TempC(void);     // returns last temperature
    int temp_ready(void);       // 1 = new data available

#ifdef __cplusplus
}
#endif

#endif