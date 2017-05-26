﻿#include "chat.hpp"
#include "client/pointers.hpp"
#include "core.hpp"
#include "common_helpers.hpp"

namespace intercept {
    namespace sqf {
        std::string call_extension(const std::string& extension_, const std::string& arguments_)
        {
            return host::functions.invoke_raw_binary(__sqf::binary__callextension__string__string__ret__string, extension_, arguments_);
        }

        std::vector<game_value> call_extension(const std::string &extension_, const std::string &function_, std::vector<game_value> &arguments_) {
            auto_array<game_value> arguments(arguments_.begin(), arguments_.end());

            game_value params_right({
                function_,
                std::move(arguments)
            });

            return __helpers::__convert_to_game_value_vector(host::functions.invoke_raw_binary(__sqf::binary__callextension__string__array__ret__array, extension_, params_right));
        }

        game_value call(const code & code_, game_value args_)
        {
            game_value args({ args_, code_ });

            set_variable(mission_namespace(), "INTERCEPT_CALL_ARGS", args);
            //#TODO these notes refer to old way call method.
            /*
            Why is this in a wrapper? Because code compiled in intercept apparently lacks
            the proper context in the SQF interpeter, so we need to be aware of that, and
            the easiest way to stay on top of it is to send the code to call into a wrapper
            in SQF itself, so the context is achieved.
            */
            host::functions.invoke_raw_unary(
                __sqf::unary__isnil__code_string__ret__bool,
                get_variable(mission_namespace(), "intercept_fnc_isNilWrapper")
            );

            // And returns are not handled correctly because of assumingly the SQF stack
            // implementation so, we just grab it from a gvar.
            return get_variable(mission_namespace(), "INTERCEPT_CALL_RETURN");
        }

        game_value call(const code & code_)
        {
            game_value args({ game_value(), code_ });

            set_variable(mission_namespace(), "INTERCEPT_CALL_ARGS", args);
            //#TODO these notes refer to old way call method.
            /*
            Why is this in a wrapper? Because code compiled in intercept apparently lacks
            the proper context in the SQF interpeter, so we need to be aware of that, and
            the easiest way to stay on top of it is to send the code to call into a wrapper
            in SQF itself, so the context is achieved.
            */
            host::functions.invoke_raw_unary(
                __sqf::unary__isnil__code_string__ret__bool,
                get_variable(mission_namespace(), "intercept_fnc_isNilWrapper")
            );

            // And returns are not handled correctly because of assumingly the SQF stack
            // implementation so, we just grab it from a gvar.
            return get_variable(mission_namespace(), "INTERCEPT_CALL_RETURN");
        }

        code compile(const std::string & sqf_)
        {
            return code(host::functions.invoke_raw_unary(__sqf::unary__compile__string__ret__code, sqf_));
        }

        std::string preprocess_file(const std::string &value_) {
            return __helpers::__string_unary_string(__sqf::unary__preprocessfile__string__ret__string, value_);
        }

        std::string preprocess_file_line_numbers(const std::string &value_) {
            return __helpers::__string_unary_string(__sqf::unary__preprocessfilelinenumbers__string__ret__string, value_);
        }

        std::string load_file(const std::string &value_) {
            return __helpers::__string_unary_string(__sqf::unary__loadfile__string__ret__string, value_);
        }

        float parse_number(const std::string &value_) {
            return __helpers::__number_unary_string(__sqf::unary__parsenumber__string__ret__scalar, value_);
        }

        float parse_number(bool value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__parsenumber__bool__ret__scalar, value_);
        }

        rv_text parse_text(const std::string& value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__parsetext__string__ret__text, value_);
        }

        game_value select_max(const game_value &array_) {
            return host::functions.invoke_raw_unary(__sqf::unary__selectmax__array__ret__any, array_);
        }

        game_value select_min(const game_value &array_) {
            return host::functions.invoke_raw_unary(__sqf::unary__selectmin__array__ret__any, array_);
        }

        game_value select(game_value array_, const code & code_) {
            return host::functions.invoke_raw_binary(__sqf::binary__select__array__code__ret__array, array_, code_);
        }

        int push_back_unique(const std::vector<game_value> &array_, const game_value &element_) {
            auto_array<game_value> base_array({ array_.begin(), array_.end() });

            return host::functions.invoke_raw_binary(__sqf::binary__pushbackunique__array__any__ret__scalar, std::move(base_array), element_);
        }

        float random(float seed_, float x_, std::optional<float> y_) {
            if (y_.has_value()) {
                game_value params_right({
                    x_,
                    *y_
                });

                return host::functions.invoke_raw_binary(__sqf::binary__random__scalar__scalar_array__ret__scalar, seed_, params_right);
            }

            return host::functions.invoke_raw_binary(__sqf::binary__random__scalar__scalar_array__ret__scalar, seed_, x_);
        }

        std::vector<game_value> apply(const std::vector<game_value> &array_, const code &code_) {
            return __helpers::__convert_to_game_value_vector(host::functions.invoke_raw_binary(__sqf::binary__apply__array__code__ret__array, array_, code_));
        }

        bool can_suspend() {
            return host::functions.invoke_raw_nular(__sqf::nular__cansuspend__ret__bool);
        }

        bool is_equal_to(const object& l_, const object& r_) {
            return host::functions.invoke_raw_binary(__sqf::binary__isequalto__any__any__ret__bool, l_, r_);
        }

        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_) {
            game_value params({
                min_,
                max_,
                value_,
                new_min_,
                new_max_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__linearconversion__array__ret__scalar, params);
        }

        float linear_conversion(float min_, float max_, float value_, float new_min_, float new_max_, bool clamp_) {
            game_value params({
                min_,
                max_,
                value_,
                new_min_,
                new_max_,
                clamp_
            });

            return host::functions.invoke_raw_unary(__sqf::unary__linearconversion__array__ret__scalar, params);
        }

        int exec_fsm(const game_value &arguments_, const std::string &file_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__execfsm__any__string__ret__scalar, arguments_, file_name_);
        }

        script exec_vm(const game_value &arguments_, const std::string &file_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__execvm__any__string__ret__script, arguments_, file_name_);
        }

        script exec_vm(const std::string& value_) {
            return script(host::functions.invoke_raw_unary(__sqf::unary__execvm__string__ret__script, value_));
        }

        bool script_done(script value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__scriptdone__script__ret__bool, value_);
        }

        void terminate(script value_) {
            host::functions.invoke_raw_unary(__sqf::unary__terminate__script__ret__nothing, value_);
        }
        void debug_fsm(float value0_, bool value1_) {
            host::functions.invoke_raw_binary(__sqf::binary__debugfsm__scalar__bool__ret__nothing, value0_, value1_);
        }

        void sleep(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__sleep__scalar__ret__nothing, value_);
        }

        void uisleep(float value_) {
            __helpers::__empty_unary_number(__sqf::unary__uisleep__scalar__ret__nothing, value_);
        }

        bool finite(float value_) {
            return __helpers::__bool_unary_number(__sqf::unary__finite__scalar_nan__ret__bool, value_);
        }

        std::string to_lower(const std::string &value_) {
            return __helpers::__string_unary_string(__sqf::unary__tolower__string__ret__string, value_);
        }

        std::string to_upper(const std::string &value_) {
            return __helpers::__string_unary_string(__sqf::unary__toupper__string__ret__string, value_);
        }

        float exec_fsm(const std::string &value_) {
            return __helpers::__number_unary_string(__sqf::unary__execfsm__string__ret__scalar, value_);
        }

        void exit() {
            __helpers::__empty_nular(__sqf::nular__exit__ret__nothing);
        }

        void save_profile_namespace() {
            __helpers::__empty_nular(__sqf::nular__saveprofilenamespace__ret__nothing);
        }

        void copy_to_clipboard(const std::string & text_) {
            __helpers::__empty_unary_string(__sqf::unary__copytoclipboard__string__ret__nothing, text_);
        }

        std::string copy_from_clipboard() {
            return __helpers::__retrieve_nular_string(__sqf::nular__copyfromclipboard__ret__string);
        }

        bool completed_fsm(float handle_) {
            return __helpers::__bool_unary_number(__sqf::unary__completedfsm__scalar__ret__bool, handle_);
        }

        game_value get_fsm_variable(int &fsm_handle_, const std::string &variable_, std::optional<game_value> default_value_) {
            if (default_value_.has_value()) {
                game_value params_right({
                    variable_,
                    *default_value_
                });

                return host::functions.invoke_raw_binary(__sqf::binary__getfsmvariable__scalar__string_array__ret__any, fsm_handle_, params_right);
            }
            return host::functions.invoke_raw_binary(__sqf::binary__getfsmvariable__scalar__string_array__ret__any, fsm_handle_, variable_);
        }

        void set_fsm_variable(float handle_, const std::string & name_, game_value value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfsmvariable__scalar__array__ret__nothing, handle_, { name_, value_ });
        }

        void set_fsm_variable(int fsm_handle_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setfsmvariable__scalar__array__ret__nothing, fsm_handle_, { variable_, value_ });
        }

        void exec(const game_value &argument_, const std::string &script_) {
            host::functions.invoke_raw_binary(__sqf::binary__exec__any__string__ret__nothing, argument_, script_);
        }


        void set_variable(const display &display_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__display__array__ret__nothing, display_, { variable_, value_ });
        }

        void set_variable(const control &control_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__control__array__ret__nothing, control_, { variable_, value_ });
        }

        void set_variable(const object &object_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__object__array__ret__nothing, object_, { variable_, value_ });
        }

        void set_variable(const group &group_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__group__array__ret__nothing, group_, { variable_, value_ });
        }

        void set_variable(const team_member &team_member_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__team_member__array__ret__nothing, team_member_, { variable_, value_ });
        }

        void set_variable(const task &task_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__task__array__ret__nothing, task_, { variable_, value_ });
        }

        void set_variable(const location &location_, const std::string &variable_, const game_value &value_) {
            host::functions.invoke_raw_binary(__sqf::binary__setvariable__location__array__ret__nothing, location_, { variable_, value_ });
        }

        void set_variable(const rv_namespace & namespace_, const std::string & var_name_, game_value value_)
        {
            //game_value args = std::vector<game_value>{ namespace_, std::vector<game_value>{ var_name_, value_ } };
            game_value args = game_value({ var_name_, value_ });

            host::functions.invoke_raw_binary(__sqf::binary__setvariable__namespace__array__ret__nothing, namespace_, args);
            //host::functions.invoke_raw_binary(__sqf::binary__call__any__code__ret__any, args, sqf::get_variable(sqf::mission_namespace(), "intercept_fnc_setVariableNamespace"));
        }


        game_value get_variable(const rv_namespace & namespace_, const std::string & var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__namespace__string__ret__any, namespace_, var_name_);
        }

        game_value get_variable(const rv_namespace & namespace_, const std::string & var_name_, game_value default_value_) {
            game_value args({
                var_name_,
                default_value_
            });
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__namespace__array__ret__any, namespace_, args);
        }

        game_value get_variable(const display & display_, const std::string & var_name_, game_value default_value_) {
            game_value args({
                var_name_,
                default_value_
            });
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__display__string_array__ret__any, display_, args);
        }

        game_value get_variable(const object & obj_, const std::string & var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__object__string__ret__any, obj_, var_name_);
        }

        game_value get_variable(const object & obj_, const std::string & var_name_, game_value default_value_) {
            game_value args({
                var_name_,
                default_value_
            });
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__object__array__ret__any, obj_, args);
        }

        game_value get_variable(const group & group_, const std::string & var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__group__string__ret__any, group_, var_name_);
        }

        game_value get_variable(const group & group_, const std::string & var_name_, game_value default_value_) {
            game_value args({
                var_name_,
                default_value_
            });
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__group__array__ret__any, group_, args);
        }

        game_value get_variable(const team_member & team_member_, const std::string & var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__team_member__string__ret__any, team_member_, var_name_);
        }

        game_value get_variable(const team_member & team_member_, const std::string & var_name_, game_value default_value_) {
            game_value args({
                var_name_,
                default_value_
            });
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__team_member__array__ret__any, team_member_, args);
        }

        game_value get_variable(const task & task_, const std::string & var_name_) {
            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__task__string__ret__any, task_, var_name_);
        }

        game_value get_variable(const control &control_, const std::string &variable_, std::optional<game_value> default_value_) {
            auto_array<game_value> params_right({
                variable_
            });
            if (default_value_.has_value()) params_right.push_back(*default_value_);

            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__control__string_array__ret__any, control_, std::move(params_right));
        }

        game_value get_variable(const task &task_, const std::string &variable_, const game_value &default_value_) {
            game_value params_right({
                variable_,
                default_value_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__task__array__ret__any, task_, params_right);
        }

        game_value get_variable(const location &location_, const std::string &variable_, const game_value &default_value_) {
            game_value params_right({
                variable_,
                default_value_
            });

            return host::functions.invoke_raw_binary(__sqf::binary__getvariable__location__array__ret__any, location_, params_right);
        }


        bool is_null(const object &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__object__ret__bool, value_);
        }

        bool is_null(const control &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__control__ret__bool, value_);
        }

        bool is_null(const display &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__display__ret__bool, value_);
        }

        bool is_null(const script &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__script__ret__bool, value_);
        }

        bool is_null(const task &value_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__task__ret__bool, value_);
        }

        script script_null() {
            return script(host::functions.invoke_raw_nular(__sqf::nular__scriptnull__ret__script));
        }

        task task_null() {
            return task(host::functions.invoke_raw_nular(__sqf::nular__tasknull__ret__task));
        }

        rv_namespace ui_namespace() {
            return rv_namespace(host::functions.invoke_raw_nular(__sqf::nular__uinamespace__ret__namespace));
        }


        std::vector<std::string> all_variables(const object &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__object__ret__array, value_));
        }
        std::vector<std::string> all_variables(const team_member &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__team_member__ret__array, value_));
        }
        std::vector<std::string> all_variables(rv_namespace value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__namespace__ret__array, value_));
        }

        std::vector<std::string> all_variables(const task &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__task__ret__array, value_));
        }


        std::vector<std::string> all_variables(const control &value_) {
            return __helpers::__convert_to_strings_vector(host::functions.invoke_raw_unary(
                __sqf::unary__allvariables__control__ret__array, value_));
        }

        bool __sqfassert(bool test_) {
            return host::functions.invoke_raw_unary(__sqf::unary__isnull__script__ret__bool, test_);
        }

        side blufor() {
            return __helpers::__retrieve_nular_side(__sqf::nular__blufor__ret__side);
        }

        object obj_null() {
            return __helpers::__retrieve_nular_object(__sqf::nular__objnull__ret__object);
        }

        side opfor() {
            return __helpers::__retrieve_nular_side(__sqf::nular__opfor__ret__side);
        }

        rv_namespace parsing_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__parsingnamespace__ret__namespace);
        }

        std::string mission_name() {
            return __helpers::__retrieve_nular_string(__sqf::nular__missionname__ret__string);
        }

        rv_namespace mission_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__missionnamespace__ret__namespace);
        }

        std::string line_break() {
            return host::functions.invoke_raw_nular(__sqf::nular__linebreak__ret__text);
        }

        side side_enemy() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sideenemy__ret__side));
        }

        side side_friendly() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sidefriendly__ret__side));
        }

        side side_logic() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sidelogic__ret__side));
        }

        side side_unknown() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__sideunknown__ret__side));
        }

        team_member team_member_null() {
            game_value ret_value = host::functions.invoke_raw_nular(__sqf::nular__teammembernull__ret__team_member);
            return team_member(host::functions.invoke_raw_nular(__sqf::nular__teammembernull__ret__team_member));
        }

        side west() {
            return side(host::functions.invoke_raw_nular(__sqf::nular__west__ret__side));
        }

        side east() {
            return __helpers::__retrieve_nular_side(__sqf::nular__east__ret__side);
        }

        side independent() {
            return __helpers::__retrieve_nular_side(__sqf::nular__independent__ret__side);
        }

        std::string profile_name() {
            return __helpers::__retrieve_nular_string(__sqf::nular__profilename__ret__string);
        }
        rv_namespace profile_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__profilenamespace__ret__namespace);
        }

        std::string profile_namesteam() {
            return __helpers::__retrieve_nular_string(__sqf::nular__profilenamesteam__ret__string);
        }

        side resistance() {
            return __helpers::__retrieve_nular_side(__sqf::nular__resistance__ret__side);
        }
        side side_ambient_life() {
            return host::functions.invoke_raw_nular(__sqf::nular__sideambientlife__ret__side);
        }

        side side_empty() {
            return host::functions.invoke_raw_nular(__sqf::nular__sideempty__ret__side);
        }

        rv_namespace current_namespace() {
            return __helpers::__retrieve_nular_namespace(__sqf::nular__currentnamespace__ret__namespace);
        }


        std::string to_fixed(float number_, int decimals_) {
            return host::functions.invoke_raw_binary(__sqf::binary__tofixed__scalar__scalar__ret__string, number_, decimals_);
        }
    }
}
