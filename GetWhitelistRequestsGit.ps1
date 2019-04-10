#Beginning of URL Whitelist Automation out of Service-Now
#smmacander@gmail.com, 3/15/2019

# Eg. User name="admin", Password="admin" for this code sample.
$User = "APIUser"
$Pass = ""

# Build auth header
$Base64AuthInfo = [Convert]::ToBase64String([Text.Encoding]::ASCII.GetBytes(("{0}:{1}" -f $User, $Pass)))

# Set proper headers
$Headers = New-Object "System.Collections.Generic.Dictionary[[String],[String]]"
$Headers.Add('Authorization',('Basic {0}' -f $Base64AuthInfo))
$Headers.Add('Accept','application/json')


# Specify endpoint uri
$URI = "https://companynamedev.service-now.com/api/now/table/sc_req_item"

# Specify HTTP method
$Method = "get"


#{request.body ? "$body = \"" :""}}

# Send HTTP request
$Response = Invoke-WebRequest -Headers $Headers -Method $Method -Uri $URI

# Print response
$Results = (($Response.Content) | ConvertFrom-Json).result | Where-Object{$_.short_description -eq "URL Whitelist Request"}

foreach($Result in $Results){

    $SysID = $Result.sys_id
    $URI2 = "https://companynamedev.service-now.com/api/sn_sc/servicecatalog/items/$SysID/variables"

    Invoke-WebRequest -Headers $Headers -Method $Method -Uri $URI2
}