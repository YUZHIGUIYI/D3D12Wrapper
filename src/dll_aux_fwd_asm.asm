.data
EXTERN FcnPtrOrg:QWORD

.code
OPTION PROLOGUE:NONE
OPTION EPILOGUE:NONE

ProxyCallOrgFcnAsm proc
    jmp qword ptr [FcnPtrOrg]
ProxyCallOrgFcnAsm endp

end

OPTION PROLOGUE:PrologueDef
OPTION EPILOGUE:EpilogueDef