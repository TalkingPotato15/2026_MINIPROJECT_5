# 현재 스크립트가 위치한 디렉터리 경로 가져오기
$scriptPath = $PSScriptRoot

# 권한을 변경할 대상 파일 목록
$targetFiles = @("nFConnect.dll", "nFConnectd.dll")

foreach ($file in $targetFiles) {
    # 대상 파일의 전체 경로 조합
    $filePath = Join-Path -Path $scriptPath -ChildPath $file

    # 파일이 실제로 존재하는지 확인
    if (Test-Path -Path $filePath) {
        try {
            # 현재 파일의 접근 제어 목록(ACL) 가져오기
            $acl = Get-Acl -Path $filePath

			# Everyone 그룹에 대한 모든 권한(FullControl) 허용 규칙 객체 생성
			$accessRule = New-Object System.Security.AccessControl.FileSystemAccessRule("Everyone", "FullControl", "Allow")
			
            # 새로운 권한 규칙을 ACL에 추가 (기존 권한에 덮어쓰거나 추가됨)
            $acl.SetAccessRule($accessRule)

			# Domain Users 그룹에 대한 모든 권한(FullControl) 허용 규칙 객체 생성
			$accessRule = New-Object System.Security.AccessControl.FileSystemAccessRule("Domain Users", "FullControl", "Allow")
 
            # 새로운 권한 규칙을 ACL에 추가 (기존 권한에 덮어쓰거나 추가됨)
            $acl.SetAccessRule($accessRule)
			
            # 변경된 ACL을 파일에 실제 적용
            Set-Acl -Path $filePath -AclObject $acl

            Write-Host "$file 파일에 Everyone 모든 권한 부여 완료." -ForegroundColor Green
        }
        catch {
            Write-Host "$file 파일 권한 변경 중 오류 발생: $_" -ForegroundColor Red
        }
    } else {
        Write-Host "$file 파일을 찾을 수 없습니다: $filePath" -ForegroundColor Yellow
    }
}