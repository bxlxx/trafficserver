/** @file

  Map of transaction overridable configuration variables and names.

  @section license License

  Licensed to the Apache Software Foundation (ASF) under one
  or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 */

#include "shared/overridable_txn_vars.h"

const std::unordered_map<std::string_view, std::tuple<const TSOverridableConfigKey, const TSRecordDataType>>
  ts::Overridable_Txn_Vars(
    {{"proxy.config.srv_enabled", {TS_CONFIG_SRV_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.http", {TS_CONFIG_HTTP_CACHE_HTTP, TS_RECORDDATATYPE_INT}},
     {"proxy.config.ssl.hsts_max_age", {TS_CONFIG_SSL_HSTS_MAX_AGE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.normalize_ae", {TS_CONFIG_HTTP_NORMALIZE_AE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.chunking.size", {TS_CONFIG_HTTP_CHUNKING_SIZE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.ssl.client.cert.path", {TS_CONFIG_SSL_CERT_FILEPATH, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.http.allow_half_open", {TS_CONFIG_HTTP_ALLOW_HALF_OPEN, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.chunking_enabled", {TS_CONFIG_HTTP_CHUNKING_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.generation", {TS_CONFIG_HTTP_CACHE_GENERATION, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.insert_client_ip", {TS_CONFIG_HTTP_ANONYMIZE_INSERT_CLIENT_IP, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.insert_forwarded", {TS_CONFIG_HTTP_INSERT_FORWARDED, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.http.cache.range.write", {TS_CONFIG_HTTP_CACHE_RANGE_WRITE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.allow_multi_range", {TS_CONFIG_HTTP_ALLOW_MULTI_RANGE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.range.lookup", {TS_CONFIG_HTTP_CACHE_RANGE_LOOKUP, TS_RECORDDATATYPE_INT}},
     {"proxy.config.net.sock_packet_tos_out", {TS_CONFIG_NET_SOCK_PACKET_TOS_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.slow.log.threshold", {TS_CONFIG_HTTP_SLOW_LOG_THRESHOLD, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.max_stale_age", {TS_CONFIG_HTTP_CACHE_MAX_STALE_AGE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.default_buffer_size", {TS_CONFIG_HTTP_DEFAULT_BUFFER_SIZE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.response_server_str", {TS_CONFIG_HTTP_RESPONSE_SERVER_STR, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.http.keep_alive_post_out", {TS_CONFIG_HTTP_KEEP_ALIVE_POST_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.net.sock_option_flag_out", {TS_CONFIG_NET_SOCK_OPTION_FLAG_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.net.sock_packet_mark_out", {TS_CONFIG_NET_SOCK_PACKET_MARK_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.websocket.active_timeout", {TS_CONFIG_WEBSOCKET_ACTIVE_TIMEOUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.connect.dead.policy", {TS_CONFIG_HTTP_CONNECT_DEAD_POLICY, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.flow_control.enabled", {TS_CONFIG_HTTP_FLOW_CONTROL_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.send_http11_requests", {TS_CONFIG_HTTP_SEND_HTTP11_REQUESTS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.body_factory.template_base", {TS_CONFIG_BODY_FACTORY_TEMPLATE_BASE, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.http.anonymize_remove_from", {TS_CONFIG_HTTP_ANONYMIZE_REMOVE_FROM, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.keep_alive_enabled_in", {TS_CONFIG_HTTP_KEEP_ALIVE_ENABLED_IN, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.doc_in_cache_skip_dns", {TS_CONFIG_HTTP_DOC_IN_CACHE_SKIP_DNS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.forward_connect_method", {TS_CONFIG_HTTP_FORWARD_CONNECT_METHOD, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.request_buffer_enabled", {TS_CONFIG_HTTP_REQUEST_BUFFER_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.down_server.cache_time", {TS_CONFIG_HTTP_DOWN_SERVER_CACHE_TIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.proxy_protocol_out", {TS_CONFIG_HTTP_PROXY_PROTOCOL_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.insert_age_in_response", {TS_CONFIG_HTTP_INSERT_AGE_IN_RESPONSE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.url_remap.pristine_host_hdr", {TS_CONFIG_URL_REMAP_PRISTINE_HOST_HDR, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.insert_request_via_str", {TS_CONFIG_HTTP_INSERT_REQUEST_VIA_STR, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.flow_control.low_water", {TS_CONFIG_HTTP_FLOW_CONTROL_LOW_WATER_MARK, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.required_headers", {TS_CONFIG_HTTP_CACHE_REQUIRED_HEADERS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.ssl.hsts_include_subdomains", {TS_CONFIG_SSL_HSTS_INCLUDE_SUBDOMAINS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.number_of_redirections", {TS_CONFIG_HTTP_NUMBER_OF_REDIRECTIONS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.keep_alive_enabled_out", {TS_CONFIG_HTTP_KEEP_ALIVE_ENABLED_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.response_server_enabled", {TS_CONFIG_HTTP_RESPONSE_SERVER_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.anonymize_remove_cookie", {TS_CONFIG_HTTP_ANONYMIZE_REMOVE_COOKIE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.request_header_max_size", {TS_CONFIG_HTTP_REQUEST_HEADER_MAX_SIZE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.parent_proxy.retry_time", {TS_CONFIG_HTTP_PARENT_PROXY_RETRY_TIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.insert_response_via_str", {TS_CONFIG_HTTP_INSERT_RESPONSE_VIA_STR, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.flow_control.high_water", {TS_CONFIG_HTTP_FLOW_CONTROL_HIGH_WATER_MARK, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.negative_caching_enabled", {TS_CONFIG_HTTP_NEGATIVE_CACHING_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.when_to_revalidate", {TS_CONFIG_HTTP_CACHE_WHEN_TO_REVALIDATE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.response_header_max_size", {TS_CONFIG_HTTP_RESPONSE_HEADER_MAX_SIZE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.anonymize_remove_referer", {TS_CONFIG_HTTP_ANONYMIZE_REMOVE_REFERER, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.global_user_agent_header", {TS_CONFIG_HTTP_GLOBAL_USER_AGENT_HEADER, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.net.sock_recv_buffer_size_out", {TS_CONFIG_NET_SOCK_RECV_BUFFER_SIZE_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.net.sock_send_buffer_size_out", {TS_CONFIG_NET_SOCK_SEND_BUFFER_SIZE_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.connect_attempts_timeout", {TS_CONFIG_HTTP_CONNECT_ATTEMPTS_TIMEOUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.websocket.no_activity_timeout", {TS_CONFIG_WEBSOCKET_NO_ACTIVITY_TIMEOUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.negative_caching_lifetime", {TS_CONFIG_HTTP_NEGATIVE_CACHING_LIFETIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.default_buffer_water_mark", {TS_CONFIG_HTTP_DEFAULT_BUFFER_WATER_MARK, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.heuristic_lm_factor", {TS_CONFIG_HTTP_CACHE_HEURISTIC_LM_FACTOR, TS_RECORDDATATYPE_FLOAT}},
     {OutboundConnTrack::CONFIG_VAR_MAX, {TS_CONFIG_HTTP_PER_SERVER_CONNECTION_MAX, TS_RECORDDATATYPE_INT}},
     {OutboundConnTrack::CONFIG_VAR_MIN, {TS_CONFIG_HTTP_SERVER_MIN_KEEP_ALIVE_CONNS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.anonymize_remove_client_ip", {TS_CONFIG_HTTP_ANONYMIZE_REMOVE_CLIENT_IP, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.open_read_retry_time", {TS_CONFIG_HTTP_CACHE_OPEN_READ_RETRY_TIME, TS_RECORDDATATYPE_INT}},
     {OutboundConnTrack::CONFIG_VAR_MATCH, {TS_CONFIG_HTTP_PER_SERVER_CONNECTION_MATCH, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.parent_proxy.fail_threshold", {TS_CONFIG_HTTP_PARENT_PROXY_FAIL_THRESHOLD, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ignore_authentication", {TS_CONFIG_HTTP_CACHE_IGNORE_AUTHENTICATION, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.anonymize_remove_user_agent", {TS_CONFIG_HTTP_ANONYMIZE_REMOVE_USER_AGENT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.connect_attempts_rr_retries", {TS_CONFIG_HTTP_CONNECT_ATTEMPTS_RR_RETRIES, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.max_open_read_retries", {TS_CONFIG_HTTP_CACHE_MAX_OPEN_READ_RETRIES, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.auth_server_session_private", {TS_CONFIG_HTTP_AUTH_SERVER_SESSION_PRIVATE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.redirect_use_orig_cache_key", {TS_CONFIG_HTTP_REDIRECT_USE_ORIG_CACHE_KEY, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ignore_client_no_cache", {TS_CONFIG_HTTP_CACHE_IGNORE_CLIENT_NO_CACHE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ims_on_client_no_cache", {TS_CONFIG_HTTP_CACHE_IMS_ON_CLIENT_NO_CACHE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ignore_server_no_cache", {TS_CONFIG_HTTP_CACHE_IGNORE_SERVER_NO_CACHE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.heuristic_min_lifetime", {TS_CONFIG_HTTP_CACHE_HEURISTIC_MIN_LIFETIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.heuristic_max_lifetime", {TS_CONFIG_HTTP_CACHE_HEURISTIC_MAX_LIFETIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.server_session_sharing.match", {TS_CONFIG_HTTP_SERVER_SESSION_SHARING_MATCH, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.http.cache.ignore_accept_mismatch", {TS_CONFIG_HTTP_CACHE_IGNORE_ACCEPT_MISMATCH, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.open_write_fail_action", {TS_CONFIG_HTTP_CACHE_OPEN_WRITE_FAIL_ACTION, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.insert_squid_x_forwarded_for", {TS_CONFIG_HTTP_INSERT_SQUID_X_FORWARDED_FOR, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.connect_attempts_max_retries", {TS_CONFIG_HTTP_CONNECT_ATTEMPTS_MAX_RETRIES, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.max_open_write_retries", {TS_CONFIG_HTTP_CACHE_MAX_OPEN_WRITE_RETRIES, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.max_open_write_retry_timeout",
      {TS_CONFIG_HTTP_CACHE_MAX_OPEN_WRITE_RETRY_TIMEOUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.forward.proxy_auth_to_parent", {TS_CONFIG_HTTP_FORWARD_PROXY_AUTH_TO_PARENT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.parent_proxy.mark_down_hostdb", {TS_CONFIG_PARENT_FAILURES_UPDATE_HOSTDB, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.negative_revalidating_enabled", {TS_CONFIG_HTTP_NEGATIVE_REVALIDATING_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.guaranteed_min_lifetime", {TS_CONFIG_HTTP_CACHE_GUARANTEED_MIN_LIFETIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.guaranteed_max_lifetime", {TS_CONFIG_HTTP_CACHE_GUARANTEED_MAX_LIFETIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.transaction_active_timeout_in", {TS_CONFIG_HTTP_TRANSACTION_ACTIVE_TIMEOUT_IN, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ignore_client_cc_max_age", {TS_CONFIG_HTTP_CACHE_IGNORE_CLIENT_CC_MAX_AGE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.negative_revalidating_lifetime", {TS_CONFIG_HTTP_NEGATIVE_REVALIDATING_LIFETIME, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.transaction_active_timeout_out", {TS_CONFIG_HTTP_TRANSACTION_ACTIVE_TIMEOUT_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.background_fill_active_timeout", {TS_CONFIG_HTTP_BACKGROUND_FILL_ACTIVE_TIMEOUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.attach_server_session_to_client", {TS_CONFIG_HTTP_ATTACH_SERVER_SESSION_TO_CLIENT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.max_proxy_cycles", {TS_CONFIG_HTTP_MAX_PROXY_CYCLES, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.cache_responses_to_cookies",
      {TS_CONFIG_HTTP_CACHE_CACHE_RESPONSES_TO_COOKIES, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.keep_alive_no_activity_timeout_in",
      {TS_CONFIG_HTTP_KEEP_ALIVE_NO_ACTIVITY_TIMEOUT_IN, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.post.check.content_length.enabled",
      {TS_CONFIG_HTTP_POST_CHECK_CONTENT_LENGTH_ENABLED, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.cache_urls_that_look_dynamic",
      {TS_CONFIG_HTTP_CACHE_CACHE_URLS_THAT_LOOK_DYNAMIC, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.transaction_no_activity_timeout_in",
      {TS_CONFIG_HTTP_TRANSACTION_NO_ACTIVITY_TIMEOUT_IN, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.keep_alive_no_activity_timeout_out",
      {TS_CONFIG_HTTP_KEEP_ALIVE_NO_ACTIVITY_TIMEOUT_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.uncacheable_requests_bypass_parent",
      {TS_CONFIG_HTTP_UNCACHEABLE_REQUESTS_BYPASS_PARENT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.transaction_no_activity_timeout_out",
      {TS_CONFIG_HTTP_TRANSACTION_NO_ACTIVITY_TIMEOUT_OUT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.background_fill_completed_threshold",
      {TS_CONFIG_HTTP_BACKGROUND_FILL_COMPLETED_THRESHOLD, TS_RECORDDATATYPE_FLOAT}},
     {"proxy.config.http.parent_proxy.total_connect_attempts",
      {TS_CONFIG_HTTP_PARENT_PROXY_TOTAL_CONNECT_ATTEMPTS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ignore_accept_charset_mismatch",
      {TS_CONFIG_HTTP_CACHE_IGNORE_ACCEPT_CHARSET_MISMATCH, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ignore_accept_language_mismatch",
      {TS_CONFIG_HTTP_CACHE_IGNORE_ACCEPT_LANGUAGE_MISMATCH, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.cache.ignore_accept_encoding_mismatch",
      {TS_CONFIG_HTTP_CACHE_IGNORE_ACCEPT_ENCODING_MISMATCH, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.connect_attempts_max_retries_dead_server",
      {TS_CONFIG_HTTP_CONNECT_ATTEMPTS_MAX_RETRIES_DEAD_SERVER, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.parent_proxy.per_parent_connect_attempts",
      {TS_CONFIG_HTTP_PER_PARENT_CONNECT_ATTEMPTS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.ssl.client.verify.server.policy", {TS_CONFIG_SSL_CLIENT_VERIFY_SERVER_POLICY, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.ssl.client.verify.server.properties",
      {TS_CONFIG_SSL_CLIENT_VERIFY_SERVER_PROPERTIES, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.ssl.client.sni_policy", {TS_CONFIG_SSL_CLIENT_SNI_POLICY, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.ssl.client.cert.filename", {TS_CONFIG_SSL_CLIENT_CERT_FILENAME, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.ssl.client.cert.path", {TS_CONFIG_SSL_CERT_FILEPATH, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.ssl.client.private_key.filename", {TS_CONFIG_SSL_CLIENT_PRIVATE_KEY_FILENAME, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.ssl.client.CA.cert.filename", {TS_CONFIG_SSL_CLIENT_CA_CERT_FILENAME, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.ssl.client.alpn_protocols", {TS_CONFIG_SSL_CLIENT_ALPN_PROTOCOLS, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.hostdb.ip_resolve", {TS_CONFIG_HTTP_HOST_RESOLUTION_PREFERENCE, TS_RECORDDATATYPE_STRING}},
     {"proxy.config.plugin.vc.default_buffer_index", {TS_CONFIG_PLUGIN_VC_DEFAULT_BUFFER_INDEX, TS_RECORDDATATYPE_INT}},
     {"proxy.config.plugin.vc.default_buffer_water_mark", {TS_CONFIG_PLUGIN_VC_DEFAULT_BUFFER_WATER_MARK, TS_RECORDDATATYPE_INT}},
     {"proxy.config.net.sock_notsent_lowat", {TS_CONFIG_NET_SOCK_NOTSENT_LOWAT, TS_RECORDDATATYPE_INT}},
     {"proxy.config.body_factory.response_suppression_mode",
      {TS_CONFIG_BODY_FACTORY_RESPONSE_SUPPRESSION_MODE, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.parent_proxy.enable_parent_timeout_markdowns",
      {TS_CONFIG_HTTP_ENABLE_PARENT_TIMEOUT_MARKDOWNS, TS_RECORDDATATYPE_INT}},
     {"proxy.config.http.parent_proxy.disable_parent_markdowns",
      {TS_CONFIG_HTTP_DISABLE_PARENT_MARKDOWNS, TS_RECORDDATATYPE_INT}}});
