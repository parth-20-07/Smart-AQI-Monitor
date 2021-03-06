// This file is meant to store the data to connect to wifi and the aws configuration data
#ifndef AWS_CONFIGURATION_H // In order to avoid double mentions and compiler errors
#define AWS_CONFIGURATION_H

//! AWS IOT config details. These are the credentials to connect with AWS and with the Wifi:
#include <pgmspace.h>
#include "Arduino.h"

#define SECRET
#define THINGNAME "MyNewESP32"

// AWS Details
int PORT = 443;
const int MQTT_PORT = 8883;
// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
const char AWS_IOT_ENDPOINT[] = "a44z12pqbjcvt-ats.iot.us-west-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAJZzGw0zdu2S/pct1RyhEUhVhA37MA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA3MTkxNzU1
MzdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCZc+M0KiWibY0HRSi8
lB93VfxRSeml4tbsp5hXWn5bcKZOjBfL92dwvJnj3M2axudQZFrufZugeXMuX0kw
aGzdjr3IKvssHjG63K+I9SyLfsM99bvhWZtfBBjswlgC0mahbvgB53fGb1hGB1xV
m7LMkvjAUQG4sOylYKDykbCeQtjQi69hJFmkzY9T3n1f8orvRd6GMFhWPkrkWpQI
JJEgf8akmF0uSCi8QAkSWxXArn4UZDlwBPpgC8wdUapqHu5fP02VVCDKbI13PlFT
HReo/BS2cZrivWt5rga55Di0dgW3F3NiCS4D/c9oTR1SgPH9aXm+D6GK3hjnEvG1
6DazAgMBAAGjYDBeMB8GA1UdIwQYMBaAFOR3RiFRwJQnGb6g/jr8OyZRZDoKMB0G
A1UdDgQWBBT6eAmYsVP9d5N46xQBHp7v4ifFmTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAygMG/d8T77Kpa9jNxEcsXU9N
bCHort1N05kV9HojRPyxqsdIv8w7F4IBg6b1Ac6xeI1ZTPJXqknJjaz80CWubApu
I6BDNxBCWlo0+Q0DsyRr+GedQBuZKF3THzbLd+4ge8JjTuQTYNJ0yiwbIePhlYwX
g6UsNjBGwLRwP6ngAwqDKbq5pwuOmf1Wrvphe6SsL9FeY0K6OLR1ZUHUJoN7L0UI
clKu5DGkWpWeVs1tAtCHCu29KY/vQPhHVmeDVauX6tkn2Ox3MaECJSRJcAQBSQY0
lhNB2Tyac1jJ0IMUNSesIrAM8YmmuiXYKIRwSVk6xDozUbDyOGbInrma/IlRuA==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAmXPjNColom2NB0UovJQfd1X8UUnppeLW7KeYV1p+W3CmTowX
y/dncLyZ49zNmsbnUGRa7n2boHlzLl9JMGhs3Y69yCr7LB4xutyviPUsi37DPfW7
4VmbXwQY7MJYAtJmoW74Aed3xm9YRgdcVZuyzJL4wFEBuLDspWCg8pGwnkLY0Iuv
YSRZpM2PU959X/KK70XehjBYVj5K5FqUCCSRIH/GpJhdLkgovEAJElsVwK5+FGQ5
cAT6YAvMHVGqah7uXz9NlVQgymyNdz5RUx0XqPwUtnGa4r1rea4GueQ4tHYFtxdz
YgkuA/3PaE0dUoDx/Wl5vg+hit4Y5xLxteg2swIDAQABAoIBABr3d50KLxTtRZRa
ff8t1J3HGZE7ePjy9Swfg7EOMRhmooM5MVFhx+bS7gRSIDur6qiBCk3Q+xFnZmtm
yVjdcQw6cnWDwCIPqFObRqm91DcrbqorzfmbIqe+85ZfzNGqIekKtEC5aZ4QoSWl
U3+j3fb/eQFq+u93AA9L/NzD55LYDNKOfoSq4UHZ55tTLHfDisGABLlcBXLwboWZ
ze0xmXlTYnhsJDcmg9z2YWGC0hi7Atoe1eDmPcztTjBT5em3OmqwD+QW3mCYqyqW
J3ZUkzs3l9piVc6fgLWSJ57DOP08zJBudksvrHoGNzD25Gqt+fCZAvrhlYKlzTul
z/eM8NkCgYEAxmdST1rW0t1iiv6yOqijsJKEqrlQzlIm5l85sA6JiQIk1lkg0f7x
CQMr2arQ/HMWOMWtJEeiZSscBW0/ON72gBBKTIcHbyGfs3U4OV78Q+VEyJpfGgzo
4YEont29jZu2yavkVBe6sY6TxdDJEkcv1vqRJwSNA1SqiFSe0nrVhfUCgYEAxf/3
qtzcaOkXAdDau52XCbqx/k+w0fJbJ9Y7Ml+NxNu4AwmMHNatxLX71n6soK6BrJNt
zALiPra+8EjX3gwOFncXFsqe4f6134PIp33JFKzH1ViM7k8k0bLtoOvNlYDHX9kT
L8qQHFn4LklLJzdz8fzYMvxFSEA4JXewqE2GOQcCgYEAkks1QhY1OR7Mvri3KtGW
gWhIMqqajse8rzmgC9VsTH4sM3Fc5fsaOA8CkmmF19/0jsATvyCi+f4jl0zKxWCC
WkOoxWz7alJcs7LHVmZXlKjFYzWQ0mCah0z5assOLhCXY3U/01H781iyVbZxzOx4
tgfkZ+TPJZmUdRoQUhsIvtECgYEAhBoEVsYmdARX6kk7NoOs+rvJ95+ZnGlzMf/3
3OLtxlLF0Zj0F2WP6Dd2v6Qibs4fDFIMplmiMy9f8xbWl3o5h/mKuRUUrjlvhKH7
JOyCVT310bzTwkehjBsx+fR5ZG7YFnXRHEisn43TTKZv8slHnUMRx+qSGuNl0nGp
tpCKpc8CgYAm/9c5MTHGSvmIaheyVP1O7KRQPi6xXjfVAtCVYrCXsrlwnSIaPs1d
k/lj5LamOfLyNnQ59Upm+kmPsKzZM/8LcoF6mxTE39epkofqqoB2HJyyIojuSrT0
o4gp6r4YSY0vau46UsPK7KOazBd148aTb6WnbYvp1RrChrYRVcE4nQ==
-----END RSA PRIVATE KEY-----
)KEY";

#endif