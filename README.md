# RomSplit

Another Saturn boot ROM split/merge utility.

## Description

Saturn cartridge boot ROM usually consists of two 8 bits flash ROM chips mapped on 16 bits data bus.
As a result, physical dump of cartridge ROM is split in two files, and this utility is here to merge them into a single file readable from hex-editor or disassembler.

Similarly, this utility makes possible to split a ROM file into two halves so it is possible to individually write flash ROM chips from a regular ROM file.

### Executing program

* Double click RomSplit.exe
* Drag and drop file(s) to convert
* Click on the Merge/Split button

### Extra

For ROM files not featuring Saturn cartridge ROM header, or whose size being different from 256KB, rom_merge_cli allows to merge two arbitrary files.

### Supported Platform

Any Windows prior to Windows 98 should be able to run this utility.

## Author

[cafe-alpha](https://ppcenter.webou.net/devblog/)

## Version History

* 1.2 - 2022 June 25
    * Added rom_merge_cli utility

* 1.0, 1.1 - 2021 September 12
    * Initial Release

## License

This project is licensed under the GPL License - see the LICENSE file for details

## Acknowledgments

* Readme template : [awesome-readme](https://github.com/matiassingers/awesome-readme)
* Cute ROM chip icon : [Jeff Israel](https://www.iconattitude.com/icons/png/8312/memory-rom.html)
* [SegaXtreme forums](https://segaxtreme.net/forums/saturn-dev.34/)
