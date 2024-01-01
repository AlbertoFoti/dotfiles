rm -rf ~/vault/crate

7z a -t7Z crate_arc media
7z a -t7Z crate_arc my_life

7z a crate_encr -p'xxxxx' -mhe=on crate_arc