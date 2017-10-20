package=carve
$(package)_version=5.3.4.2
$(package)_download_path=https://codeload.github.com/bitbaba/carve/tar.gz
$(package)_download_file=5.3.4.2
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=ba0085307d8f1e3cf8c6569598f26eb926ec91640edc19ae6c9a2bb1f3f010e1

define $(package)_preprocess_cmds
  ./autogen.sh
endef

define $(package)_set_vars
  $(package)_config_opts=--with-pic
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
endef
