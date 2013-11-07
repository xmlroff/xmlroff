<?xml version="1.0" encoding="utf-8"?>
<!-- XSL stylesheet to generate individual HTML report for a test. -->
<!-- Usage:
     xsltproc -o index.html -novalid testsuccess.xsl testsuccess.xsl
-->

<!-- Copyright (C) 2001 Sun Microsystems -->
<!-- Copyright (C) 2007-2009 Menteith Consulting Ltd -->

<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:exsl="http://exslt.org/common"
                extension-element-prefixes="exsl"
                version="1.0">

  <xsl:strip-space elements="*"/>

  <xsl:template name="results-doc">
    <xsl:param name="pdf"/>
    <xsl:param name="results"/>
    <xsl:param name="results-top-base"
      select="($results/ancestor::*/@base)[1]"/>
    <xsl:param name="id"/>

    <xsl:param name="test"
      select="$testsuite-nodes[@profile = $results-top-base/../@profile]//test[@id = $id]"/>

    <xsl:if test="$DEBUG">
      <xsl:message>results-doc::</xsl:message>
      <xsl:message>pdf: '<xsl:value-of select="$pdf"/>'</xsl:message>
      <xsl:message>results: '<xsl:value-of select="$results"/>'</xsl:message>
      <xsl:message>results-top-base: '<xsl:value-of select="$results-top-base"/>'</xsl:message>
      <xsl:message>profile: '<xsl:value-of select="$results-top-base/../@profile"/>'</xsl:message>
      <xsl:message>test::</xsl:message>
      <xsl:message>id: '<xsl:value-of select="$id"/>'</xsl:message>
      <xsl:message>text: '<xsl:value-of select="$test"/>'</xsl:message>
      <xsl:message>xml: '<xsl:value-of select="$test/@xml"/>'</xsl:message>
      <xsl:message>xsl: '<xsl:value-of select="$test/@xsl"/>'</xsl:message>
      <xsl:message>result: '<xsl:value-of select="$test/@result"/>'</xsl:message>
    </xsl:if>
    
    <xsl:variable name="testsuites-dirname">
      <xsl:call-template name="dirname">
        <xsl:with-param name="string" select="$TESTSUITES"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="this-testsuite-dirname">
      <xsl:call-template name="dirname">
        <xsl:with-param name="string"
          select="$testsuite-files[document(.,document($TESTSUITES))/testsuite/@profile = $results-top-base/../@profile]"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="test-file-dirname">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="'..'"/>
        <xsl:with-param name="dirname2">
          <xsl:call-template name="merge-dirnames">
            <xsl:with-param name="dirname1" select="$testsuites-dirname"/>
            <xsl:with-param name="dirname2" select="$this-testsuite-dirname"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:call-template>
      <xsl:text>/</xsl:text>
      <xsl:for-each select="$test/ancestor::*/@base">
        <xsl:value-of select="."/>
        <xsl:text>/</xsl:text>
      </xsl:for-each>
    </xsl:variable>

		<xsl:call-template name="results-html">
			<xsl:with-param name="results" select="$results" />
			<xsl:with-param name="id" select="$id" />
			<xsl:with-param name="test" select="$test" />
			<xsl:with-param name="pdf" select="$pdf" />
			<xsl:with-param name="results-top-base" select="$results-top-base" />
			<xsl:with-param name="test-file-dirname" select="$test-file-dirname" />
			<xsl:with-param
					name="scripts-base"
					select="concat('/', $PROJECT_NAME, '/', $BASENAME)"/>
		</xsl:call-template>
</xsl:template>

<xsl:template name="results-html">
	<xsl:param name="results"/>
	<xsl:param name="id"/>
	<xsl:param name="test"/>
	<xsl:param name="pdf"/>
	<xsl:param name="results-top-base"/>
	<xsl:param name="test-file-dirname"/>
	<xsl:param name="scripts-base"/>
      <html>
        <head>
          <title>
            <xsl:value-of select="$id"/>
            <xsl:text> - </xsl:text>
            <xsl:value-of select="$results/ancestor::testsuite/@profile"/>
            <xsl:text> - </xsl:text>
            <xsl:for-each select="$results/ancestor::*/@base">
              <xsl:value-of select="."/>
              <xsl:text>/</xsl:text>
            </xsl:for-each>
            <xsl:value-of select="$id"/>
          </title>
          <link rel="stylesheet" type="text/css" href="../style.css"/>
        </head>
        <body class="results">
          <div>
            <h1 class="coloured">
              <span style="font-size: 60%">
                <xsl:value-of select="$results/ancestor::testsuite/@profile"/>
              </span>
              <br/>
              <xsl:for-each select="$results/ancestor::*/@base">
                <xsl:value-of select="."/>
                <xsl:text>/</xsl:text>
              </xsl:for-each>
              <xsl:value-of select="$id"/>
            </h1>
          </div>
          <xsl:if test="$date">
            <p>Report created: <xsl:value-of select="$date"/></p>
          </xsl:if>
          <table>
            <tr>
              <th rowspan="2" style="background-color: white">Test</th>
              <td colspan="4" class="coloured2"><xsl:value-of select="$test"/></td>
            </tr>
            <tr>
              <td style="background-color: white">
                <b>FO </b>
                <xsl:value-of select="$test/@fo"/>
              </td>
              <td style="background-color: white">
                <b>XML </b>
                <xsl:if test="$test/@xml">
                  <xsl:call-template name="munged-a">
                    <xsl:with-param name="href" select="$test/@xml"/>
                    <xsl:with-param name="content">
                      <xsl:value-of select="$test/@xml"/>
                    </xsl:with-param>
                    <xsl:with-param name="test-file-dirname"
                      select="$test-file-dirname"/>
                  </xsl:call-template>
                </xsl:if>
              </td>
              <td style="background-color: white">
                <b>XSL </b>
                <xsl:if test="$test/@xsl">
                  <xsl:call-template name="munged-a">
                    <xsl:with-param name="href" select="$test/@xsl"/>
                    <xsl:with-param name="content">
                      <xsl:value-of select="$test/@xsl"/>
                    </xsl:with-param>
                    <xsl:with-param name="test-file-dirname"
                      select="$test-file-dirname"/>
                  </xsl:call-template>
                </xsl:if>
              </td>
              <td style="background-color: white">
                <b>Results </b>
                <xsl:choose>
                  <xsl:when test="$test/@results">
                    <xsl:call-template name="munged-a">
                      <xsl:with-param name="href" select="$test/@results"/>
                      <xsl:with-param name="content">
                        <xsl:value-of select="$test/@results"/>
                      </xsl:with-param>
                      <xsl:with-param name="test-file-dirname"
                        select="$test-file-dirname"/>
                    </xsl:call-template>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>None</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
            </tr>
            <tr>
              <th rowspan="2" style="background-color: white">Result</th>
              <td style="background-color: white">
                <b>PDF </b>
                <xsl:choose>
                  <xsl:when test="$pdf and $pdf/@size != 0">
                    <a href="{$id}.pdf"><xsl:value-of select="$id"/>.pdf</a>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:text>No output</xsl:text>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
              <td colspan="1" style="background-color: white">
                <b>Log </b>
                <a href="{$id}.log">
                  <xsl:value-of select="$id"/>
                  <xsl:text>.log</xsl:text>
                </a>
              </td>
              <td colspan="2"  style="background-color: white">
                <b>Pages </b>
                <xsl:for-each select="$pdf/pwd/png">
									<xsl:variable name="name" select="@name"/>
                  <a href="#page{position()}">
										<xsl:if test="../../diff/png[@name = $name]/@size != 0">
											<xsl:attribute name="style">
												<xsl:text>color: white; background-color: red</xsl:text>
											</xsl:attribute>
										</xsl:if>
										<xsl:value-of select="position()"/>
									</a>
                  <xsl:if test="position() != last()">
                    <xsl:text>, </xsl:text>
                  </xsl:if>
                </xsl:for-each>
              </td>
            </tr>
            <tr>
              <td colspan="4" style="background-color: white">
                <xsl:choose>
                  <xsl:when test="$FORM">
                    <xsl:call-template name="results-form">
                      <xsl:with-param name="id" select="$id"/>
                      <xsl:with-param name="results" select="$results"/>
                      <xsl:with-param name="results-top-base" select="$results-top-base"/>
                      <xsl:with-param name="scripts-base" select="$scripts-base"/>
                    </xsl:call-template>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:call-template name="results-static">
                      <xsl:with-param name="id" select="$id"/>
                      <xsl:with-param name="results" select="$results"/>
                      <xsl:with-param name="results-top-base" select="$results-top-base"/>
                    </xsl:call-template>
                  </xsl:otherwise>
                </xsl:choose>
              </td>
            </tr>
          </table>

          <table>
            <xsl:for-each select="$pdf/pwd/png">
              <xsl:variable name="name" select="@name"/>
              <tr class="coloured3">
                <td>
                  <a name="page{position()}">
                    <span class="png-title">
                      <xsl:text>Page </xsl:text>
                      <xsl:value-of select="position()"/>
                      <xsl:text> </xsl:text></span>
                    <span>
		      <xsl:if
			  test="../../diff/png[@name=$name]/@size != 0">
			<xsl:attribute name="style">color: #F00; font-weight: bold</xsl:attribute>
		      </xsl:if>
		      <xsl:value-of select="$name"/>
		    </span>
                  </a>
                </td>
                <xsl:if test="$REFERENCE">
                  <xsl:if test="../../ref/png[@name=$name]">
                    <td>
		      <xsl:if
			  test="../../diff/png[@name=$name]/@size != 0">
			<xsl:attribute name="style">color: #0FF</xsl:attribute>
		      </xsl:if>
                      <span class="png-title">Reference</span>
                    </td>
                  </xsl:if>
                  <xsl:if test="../../stereo/png[@name=$name]">
                    <td>
                      <span class="png-title">Stereo</span>
                    </td>
                  </xsl:if>
                </xsl:if>
              </tr>
              <tr>
                <td>
                  <img src="{$name}" alt="{$name} current result"
                    border="0"/>
                </td>
                <xsl:if test="$REFERENCE">
                  <xsl:if test="../../ref/png[@name=$name]">
                    <td>
                      <xsl:choose>
                        <xsl:when test="../../diff/png[@name=$name]/@size != 0">
                          <img src="ref/{$name}" alt="{$name} reference result"
                            border="0"/>
                        </xsl:when>
                        <xsl:otherwise>
                          <p style="background-color: white">Reference is identical to current.</p>
                        </xsl:otherwise>
                      </xsl:choose>
                    </td>
                  </xsl:if>
                  <xsl:if test="../../stereo/png[@name=$name]">
                    <td>
                      <xsl:choose>
                        <xsl:when test="../../diff/png[@name=$name]/@size != 0">
                          <img src="stereo/{$name}" alt="{$name} stereo result"
                            border="0"/>
                        </xsl:when>
                        <xsl:otherwise>
                          <p style="background-color: white">Reference is identical to current.</p>
                        </xsl:otherwise>
                      </xsl:choose>
                    </td>
                  </xsl:if>
                </xsl:if>
              </tr>
            </xsl:for-each>
          </table>
        </body>
      </html>
  </xsl:template>

  <xsl:template name="results-form">
    <xsl:param name="results"/>
    <xsl:param name="id"/>
    <xsl:param name="results-top-base"/>
		<xsl:param name="scripts-base"/>
    <xsl:if test="$DEBUG">
      <xsl:message>results-doc::</xsl:message>
      <xsl:message>results: '<xsl:value-of select="$results"/>'</xsl:message>
      <xsl:message>results-top-base: '<xsl:value-of select="$results-top-base"/>'</xsl:message>
      <xsl:message>profile: '<xsl:value-of select="$results-top-base/../@profile"/>'</xsl:message>
    </xsl:if>
        <form action="{$scripts-base}/update-results.pl" method="post">
          <input type="hidden" name="id" value="{$id}"/>
          <input type="hidden" name="top-base" value="{$results-top-base}"/>
          <input type="hidden" name="path" value="{($results/ancestor::*/@base)[1]}/{$id}"/>
    <table bgcolor="white" border="0" cellspacing="0">
          <tr>
            <td style="background-color: white">Agreement:</td>
            <td style="background-color: white">
              <select name="agreement">
                <option value="full">
                  <xsl:if test="$results/@agreement='full'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Full</xsl:text>
                </option>
                <option value="issues">
                  <xsl:if test="$results/@agreement='issues'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Issues</xsl:text>
                </option>
              </select>
            </td>
          </tr>
          <tr>
            <td style="background-color: white">Future support:</td>
            <td style="background-color: white">
              <select name="futuresupport">
                <option value="full">
                  <xsl:if test="$results/@futuresupport='full'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Full</xsl:text>
                </option>
                <option value="partial">
                  <xsl:if test="$results/@futuresupport='partial'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Partial</xsl:text>
                </option>
                <option value="none">
                  <xsl:if test="$results/@futuresupport='none'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>None</xsl:text>
                </option>
                <option>
                  <xsl:if test="not($results/@futuresupport)">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                </option>
              </select>
            </td>
          </tr>
          <tr>
            <td style="background-color: white">Spec problem:</td>
            <td style="background-color: white">
              <select name="specproblem">
                <option value="yes">
                  <xsl:if test="$results/@specproblem='yes'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Yes</xsl:text>
                </option>
                <option value="no">
                  <xsl:if test="not($results/@specproblem) or $results/@specproblem='no'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>No</xsl:text>
                </option>
              </select>
            </td>
          </tr>
          <tr>
            <td style="background-color: white">Test problem:</td>
            <td style="background-color: white">
              <select name="testproblem">
                <option value="yes">
                  <xsl:if test="$results/@testproblem='yes'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Yes</xsl:text>
                </option>
                <option value="no">
                  <xsl:if test="not($results/@testproblem) or $results/@testproblem='no'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>No</xsl:text>
                </option>
              </select>
            </td>
          </tr>
          <tr>
            <td style="background-color: white">Further info:</td>
            <td style="background-color: white">
              <textarea name="comment" rows="1" cols="60">
                <xsl:value-of select="."/>
              </textarea>
            </td>
          </tr>
          <tr>
            <td style="background-color: white">&#160;</td>
            <td style="background-color: white">
              <input type="submit" name="update" value="Update"/>&#160;&#160;<input type="reset"/>
            </td>
          </tr>
          <tr>
            <td colspan="2">Note that "Update" updates the XML
source for this report and <b>does not</b> regenerate this HTML page.
            </td>
          </tr>
    </table>
        </form>
  </xsl:template>

  <xsl:template name="results-static">
    <xsl:param name="results"/>
    <table bgcolor="white" border="0" cellspacing="0">
        <tr>
          <td style="background-color: white">Agreement:</td>
          <td width="10%">
            <xsl:attribute name="class">
              <xsl:choose>
                <xsl:when test="$results/@agreement = 'issues' and . = $not-verified-string">
                  <xsl:text>other</xsl:text>
                </xsl:when>
                <xsl:when test="$results/@agreement = 'full'">
                  <xsl:text>full</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:text>differ</xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:attribute>
            <xsl:choose>
              <xsl:when test="$results/@agreement = 'full'">
                <xsl:text>Full</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>Issues</xsl:text>
              </xsl:otherwise>
            </xsl:choose>
          </td>
          <td></td>
        </tr>
        <tr>
          <td style="background-color: white">Future support:</td>
          <td style="background-color: white">
            <xsl:choose>
              <xsl:when test="$results/@futuresupport = 'full'">
                <xsl:text>Full</xsl:text>
              </xsl:when>
              <xsl:when test="$results/@futuresupport = 'partial'">
                <xsl:text>Partial</xsl:text>
              </xsl:when>
              <xsl:when test="not($results/@futuresupport)">
                <xsl:text>&#160;</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>None</xsl:text>
              </xsl:otherwise>
            </xsl:choose>
          </td>
          <td></td>
        </tr>
        <tr>
          <td style="background-color: white">Spec problem:</td>
          <td>
            <xsl:attribute name="class">
              <xsl:choose>
                <xsl:when test="$results/@specproblem = 'yes'">
                  <xsl:text>spec</xsl:text>
                </xsl:when>
                <xsl:otherwise>other</xsl:otherwise>
              </xsl:choose>
            </xsl:attribute>
            <xsl:choose>
              <xsl:when test="$results/@specproblem = 'yes'">
                <xsl:text>Yes</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>No</xsl:text>
              </xsl:otherwise>
            </xsl:choose>
          </td>
          <td></td>
        </tr>
        <tr>
          <td style="background-color: white">Test problem:</td>
          <td>
            <xsl:attribute name="class">
              <xsl:choose>
                <xsl:when test="$results/@testproblem = 'yes'">
                  <xsl:text>test</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:text>other</xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:attribute>
            <xsl:choose>
              <xsl:when test="$results/@testproblem = 'yes'">
                <xsl:text>Yes</xsl:text>
              </xsl:when>
              <xsl:otherwise>
                <xsl:text>No</xsl:text>
              </xsl:otherwise>
            </xsl:choose>
          </td>
          <td></td>
        </tr>
        <tr>
          <td style="background-color: white">Further info:</td>
          <td style="background-color: white" colspan="2">
            <xsl:apply-templates/>
          </td>
        </tr>
    </table>
  </xsl:template>

</xsl:stylesheet>
