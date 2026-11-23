/* Set or clear the string field at offset 0xA6. */
extern "C" {
char* strcpy(char*, const char*);
void fn_80025F88(char* o, const char* s) {
    if (s) strcpy(o + 0xA6, s);
    else o[0xA6] = 0;
}
}
