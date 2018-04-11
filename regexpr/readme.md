var_type = "((?:unsigned )?(?:void|char|short|int|long|float|double|bool))((?:(?: )*\*)+|(?= |;|\),))"
comment = "(?:\/\/.*)|(?:\/\*(?:.*[\n\r]?)+?\*\/)"

^((?:signed|unsigned|void|char|short|int|long|float|double|bool)(?: )*)+(?:(?: )*\*)*
