/*
 *
 * Copyright 2019 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPCPP_SECURITY_SERVER_CREDENTIALS_H
#define GRPCPP_SECURITY_SERVER_CREDENTIALS_H

#include <grpcpp/security/server_credentials_impl.h>

namespace grpc_impl {

class Server;
}  // namespace grpc_impl
namespace grpc {

typedef ::grpc_impl::ServerCredentials ServerCredentials;

/// Options to create ServerCredentials with SSL
struct SslServerCredentialsOptions {
  /// \warning Deprecated
  SslServerCredentialsOptions()
      : min_tls_version(TLS1_2),
        max_tls_version(TLS1_3),
        force_client_auth(false),
        client_certificate_request(GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE) {}
  SslServerCredentialsOptions(
      grpc_ssl_client_certificate_request_type request_type)
      : min_tls_version(TLS1_2),
        max_tls_version(TLS1_3),
        force_client_auth(false),
        client_certificate_request(request_type) {}

  struct PemKeyCertPair {
    std::string private_key;
    std::string cert_chain;
  };
  std::string pem_root_certs;
  std::vector<PemKeyCertPair> pem_key_cert_pairs;
  grpc_tls_version min_tls_version;
  grpc_tls_version max_tls_version;
  /// \warning Deprecated
  bool force_client_auth;

  /// If both \a force_client_auth and \a client_certificate_request
  /// fields are set, \a force_client_auth takes effect, i.e.
  /// \a REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY
  /// will be enforced.
  grpc_ssl_client_certificate_request_type client_certificate_request;
};

std::shared_ptr<ServerCredentials> SslServerCredentials(
    const SslServerCredentialsOptions& options);

std::shared_ptr<ServerCredentials> InsecureServerCredentials();

namespace experimental {

typedef ::grpc_impl::experimental::AltsServerCredentialsOptions
    AltsServerCredentialsOptions;

std::shared_ptr<ServerCredentials> AltsServerCredentials(
    const AltsServerCredentialsOptions& options);

std::shared_ptr<ServerCredentials> LocalServerCredentials(
    grpc_local_connect_type type);

/// Builds TLS ServerCredentials given TLS options.
std::shared_ptr<ServerCredentials> TlsServerCredentials(
    const ::grpc::experimental::TlsCredentialsOptions& options);

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SECURITY_SERVER_CREDENTIALS_H
