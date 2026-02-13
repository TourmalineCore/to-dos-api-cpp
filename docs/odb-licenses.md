# ODB (Object-Relational Mapping) license

We use several packages in the project:
| Package          | License* (which we are now experiencing)                                                       |
| ---------------- | -------------------------------------------------------------- |
| odb              | [GNU GPL v3](https://www.codesynthesis.com/licenses/gpl-3.txt) |
| libodb           | [GNU GPL v2](https://www.codesynthesis.com/licenses/gpl-2.txt) |
| libodb-dev       | [GNU GPL v2](https://www.codesynthesis.com/licenses/gpl-2.txt) |
| libodb-pgsql     | [GNU GPL v2](https://www.codesynthesis.com/licenses/gpl-2.txt) |
| libodb-pgsql-dev | [GNU GPL v2](https://www.codesynthesis.com/licenses/gpl-2.txt) |

We comply with the specified licenses because:
1. The repository is public (open source)
2. We do not use this project for commercial purposes.

In addition to the licenses listed in the table, ODB offers other project licensing alternatives:
1. Commercial Proprietary License (CPL)
2. Free Proprietary License (FPL)

*License information is taken from the official [ODB repository](https://github.com/codesynthesis-com/odb/blob/master/LICENSE). 

## GNU General Public License (GPL) version 2 and GNU General Public License (GPL) version 3

The GNU General Public License (GPL) version 2 and the GNU General Public License (GPL) version 3 have the same licensing rules.

ODB has a license in the following cases:
1. If the application is used only within the organization, for example, running it on company servers, then publication of the source code is not required. As ODB itself says, such an application is unlikely to become a source of significant earnings, so ODB can be used free of charge under the GPL license.

Quote:
```
If the application that is based on ODB is only used internally within the organization, then it is unlikely to be a source of significant revenue while its utility is most likely limited to this organization. As a result, in this case, ODB can be used under the GPL without giving anything back.

On the other hand, if you only use your application within your organization, such as running it on your company's servers, then you do not need to make your source code public.
```

2. If the application is used outside the organization, ODB can be used free of charge in accordance with the GPL license, but the source code of the application must be open.

Quote:
```
If the application that is based on ODB is distributed to third parties, then it is likely to be a source of revenue and/or to have broad utility. In this case the organization has two choices: It can use ODB free of charge under the GPL but has to make the source code for the entire application publicly available also free of charge (making the application essentially free).
```

If ODB has this license, then the project must also be licensed under the GNU General Public License (GPL) version 2, and the source code must be open, except for private internal use within the company.

## Special case: ODB Non-Commercial Use and Evaluation License (NCUEL)

```
ODB can also be used free of charge non-commercially or for evaluation with non-free editions of commercial databases (Oracle, SQL Server) under the terms of the ODB Non-Commercial Use and Evaluation License (NCUEL) (a source-available license).
```

## Commercial Proprietary License (CPL)

If you do not want to be bound by the terms of the GPL, you can purchase a Commercial Proprietary License (CPL).

This type of license allows the project to be used for commercial purposes, even in cases where the source code is closed.

Quote:
```
Additional benefits of the CPL include:
-Royalty-free runtime (no runtime licenses)
- Application source code stays private
- Legal assurances, warranties, and indemnification
- Commercial-grade technical support
- Full-time, dedicated development team provides ongoing maintenance, development, testing, and documentation
- Single vendor to hold accountable
```

## Free Proprietary License (FPL)

This is a free version of the Commercial Proprietary License (CPL). It allows you to use ODB in a closed application free of charge and without any GPL restrictions, provided that the amount of generated database support code in any individual release of the application does not exceed 10,000 lines.

Quote:
```
In addition to the Commercial Proprietary License we offer a free version for handling small object models. This license allows you to use ODB in a proprietary (closed-source) application free of charge and without any of the GPL restrictions provided that the amount of the generated database support code in any single release of your application does not exceed 10,000 lines.
```

### What is <u>generated database support code</u>??

The ODB compiler analyzes classes and generates the necessary code for working with the database. Such files have the following extensions: *.cxx, *.hxx, and *.ixx.

To start using ODB under FPL, you must obtain a copy of the license agreement.

![odb-license-table](./images/odbLicenseTable.png)

## Conclusion

The repository cannot have an MIT license while continuing to use ODB, as ODB has a GNU GPL v2 license, which is not backward compatible with MIT.

In the case of commercial use requiring closed source code, a license will be required, unless the <u>generated database support code</u> is less than 10,000 lines in size.

## References

[Reference to GNU General Public License (GPL) version 2.](https://www.codesynthesis.com/licenses/gpl-2.txt)  
[Reference to GNU General Public License (GPL) version 3.](https://www.codesynthesis.com/licenses/gpl-3.txt)  
[Reference to the ODB Non-Commercial Use and Evaluation License (NCUEL).](https://www.codesynthesis.com/licenses/ncuel.txt)
[Licensing section on the Code Synthesis website.](https://www.codesynthesis.com/products/odb/license.xhtml#1)  
[Answers to questions about the GNU GPL v2 license, including an answer to a question about a closed-source project and the GNU GPL v2 license.](https://www.gnu.org/licenses/old-licenses/gpl-2.0-faq.en.html#GPLRequireSourcePostedPublic)  
[Report from the C++ Russia conference “Software licenses: theory that saves you from financial disaster”.](https://cppconf.ru/archive/2025/talks/06ea4864b2244143baefe7a725f12177/)
