#define CAT(a, b) CAT_I(a, b)
#define CAT_I(a, b) CAT_II(~, a ## b)
#define CAT_II(p, res) res