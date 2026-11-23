/* Copy the four-entry float tables before indexing, as in the original. */
extern "C" {
struct Vec4 { float a[4]; };
extern Vec4 lbl_803692A0;
extern Vec4 lbl_80369290;
float fn_801315EC(void*,int i) { Vec4 a=lbl_803692A0;return a.a[i]; }
float fn_801317EC(void*,int i) { Vec4 a=lbl_80369290;return a.a[i]; }
}
