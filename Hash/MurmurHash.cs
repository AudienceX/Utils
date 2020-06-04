public static string midgen(string data)
{
    return uln_sign_murmur2_64(Encoding.UTF8.GetBytes(data)).ToString();
}

private static ulong uln_sign_murmur2_64(byte[] src)
{
    ulong len = (ulong)src.Length;
    if (len < 1) return 0;
    ulong sign1 = 0;
    ulong sign2 = 0;

    ulong ret = MurmurHash2A_64(src, len, 0);
    sign1 = (ret >> 32) & 0x0ffffffff;
    sign2 = ret & 0x0ffffffff;
    ulong sign = ( sign1 << 32) +sign2;
    return sign;
}

private static ulong MurmurHash2A_64(byte[] src, ulong len, ulong seed) {
    //ulong m = Convert.ToUInt64("0xc6a4a7935bd1e995", 16);
    ulong m = 0xc6a4a7935bd1e995;
    int r = 47;
    ulong h = seed ^ (len * m);
    int startIdx = 0;
    while ((ulong)(startIdx + sizeof(ulong)) <= len)
    {
        ulong k = BitConverter.ToUInt64(src, startIdx);
        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
        startIdx += sizeof(ulong);
    }

    if ((ulong)startIdx < len)
    {
        ulong size = len - (ulong)startIdx;
        byte[] arr = new byte[size];
        Array.Copy(src, startIdx, arr,  0, (int)size);
        for (int i = 0; i < (int)(len & 7); i++)
        {
            //每个字节偏移 8 位
            h ^= ((ulong)arr[i]) << sizeof(ulong) * i;
        }
        h *= m;


    }
    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}
