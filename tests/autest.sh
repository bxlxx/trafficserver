#!/bin/bash
# vim: sw=4:ts=4:softtabstop=4:ai:et

#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

fail()
{
    echo $1
    exit 1
}
./prepare_proxy_verifier.sh || fail "Failed to install Proxy Verifier."
pushd $(dirname $0) > /dev/null
export PYTHONPATH=$(pwd):$PYTHONPATH
./test-env-check.sh || fail "Failed Python environment checks."
# this is for rhel or centos systems
echo "Environment config finished. Running AuTest..."
pipenv run autest "$@" -D gold_tests
ret=$?
popd > /dev/null
exit $ret
