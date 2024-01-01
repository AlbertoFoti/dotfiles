
Compress and encrypt

    7z a -t7z <dst> <src>

    7z a <dst> -p'<passwd>' -mhe=on <src>

Decrypt and decompress

    7z x <src> -p'<passwd>'

    7z x <src> -o<dst>