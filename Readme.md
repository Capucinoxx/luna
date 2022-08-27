# luna DB

```
représentation des données sur le disque

+--------------------------------------------------------------------+
| HEADER (count, end_offset, crc)                                    |
+--------------------------------------------------------------------+
| DATA                                                               |
|                                                                    |
| sérialisation des valeurs                                          |
| +----------------------------------------------------------------+ |
| | size: 4bytes | key_size: 4bytes | key | val_size: 4bytes | val | |
| +----------------------------------------------------------------+ |
|                               ...                                  |
|                             n tuples                               |
|                               ...                                  |
| +----------------------------------------------------------------+ |
| | size: 4bytes | key_size: 4bytes | key | val_size: 4bytes | val | |
| +----------------------------------------------------------------+ |
+--------------------------------------------------------------------+
```