<?xml version="1.0" encoding="utf-8"?>
<!-- $Id: testsuccess.xsl,v 1.15 2007/02/05 18:26:27 menteith Exp $ -->
<!-- XSL stylesheet to generate testsuccess.html from testresults.xml and
     testsuccess.xml. -->
<!-- Usage:
     xsltproc -o index.html -novalid testsuccess.xsl testsuccess.xsl
-->

<!-- Copyright (C) 2001 Sun Microsystems -->
<!-- See COPYING for the status of this software. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:saxon="http://icl.com/saxon"
                extension-element-prefixes="saxon"
                version="1.0">

  <xsl:import href="config.xsl"/>
  <xsl:import href="common.xsl"/>
  
  <xsl:import href="coverage.xsl"/>

  <xsl:output method="html" indent="no" encoding="UTF-8"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="testsuccess-node"
    select="document($TESTSUCCESS)/testsuccess"/>

  <!-- Set of filenames - probably relative - of the testsuite.xml files -->
  <xsl:variable name="testsuite-files"
    select="document($TESTSUITES)/testsuites/testsuite/@href"/>

  <!-- Set of <testsuite> nodes -->
  <xsl:variable name="testsuite-nodes"
    select="document($testsuite-files, document($TESTSUITES))/testsuite"/>

  <xsl:variable name="testresults-doc"
    select="document($TEST_RESULTS)"/>
  <xsl:key name="results" match="testresult" use="@results"/>
  <xsl:key name="PDF" match="pdf" use="@name"/>

  <xsl:variable name="not-verified-string"
    select="'Results not yet verified'"/>

  <!-- Common navigation table component -->
  <xsl:template name="nav-table">
    <xsl:param name="up-id"/>
    <xsl:param name="top-id"/>

    <xsl:if test="$up-id or $top-id">
      <table align="right">
        <tr>
          <td align="right">
            <xsl:if test="$up-id">
              <xsl:text/>[<a href="#{$up-id}">Up</a>]<xsl:text/>
            </xsl:if>
            <xsl:if test="$top-id">
              <xsl:text/> [<a href="#{$top-id}">Top</a>]<xsl:text/>
            </xsl:if>
          </td>
        </tr>
      </table>
    </xsl:if>
  </xsl:template>

  <xsl:variable name="page-title">
    <xsl:text/>XSL Test Suite: <xsl:value-of select="$TITLE"/>
  </xsl:variable>

  <xsl:template match="/">
  <xsl:if test="$DEBUG">
    <xsl:message>testsuite-files: '<xsl:value-of select="$testsuite-files"/>'</xsl:message>
    <xsl:message>testsuite-nodes: '<xsl:value-of select="$testsuite-nodes"/>'</xsl:message>
  </xsl:if>
  
    <xsl:apply-templates select="$testresults-doc" mode="testresults"/>
  </xsl:template>

  <xsl:template match="/" mode="testresults">
    <html>
      <head>
        <title>
          <xsl:value-of select="$page-title"/>
        </title>
        <style type="text/css">
          body { background-color: white}
    td.full {background-color: green; color: white; text-align: center}
    td.future {background-color: palegreen; text-align: center}
    td.differ {background-color: yellow; text-align: center}
    td.test {background-color: orange; text-align: center}
    td.spec {background-color: red; text-align: center}
    td.other {background-color: white; text-align: center}
    td.not-yet-verified {background-color: silver; text-align: center}
    .coloured {background-color: #DDEEFF}
    td.coloured {border-top: 3pt solid white}
    .coloured2 {background-color: #CCDDFF}
    td.coloured2 {border-top: 3pt solid white}
    .coloured3 {background-color: #BBCCFF}
    td.coloured3 {border-top: 6pt solid white}
    .coloured4 {background-color: #99BBFF}
    td.coloured4 {border-top: 18pt solid white}
    .coloured5 {background-color: #99AAFF}
    tr.diff {background-color: #FFEEEE}
        </style>
      </head>
      <body>
        <h1>
          <xsl:value-of select="$page-title"/>
        </h1>
        <xsl:if test="$date">
          <p>Report created: <xsl:value-of select="$date"/></p>
        </xsl:if>
        <xsl:apply-templates/>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="testsuite">
    <xsl:variable name="testsuite-id"
      select="translate(@profile, ' ', '-')"/>
    <xsl:variable name="all-testresults"
      select=".//testresult"/>
    <xsl:variable name="full-results-count"
      select="count($all-testresults[@agreement='full' and . != $not-verified-string])"/>
    <xsl:variable name="issues-results-count"
      select="count($all-testresults[@agreement='issues' and . != $not-verified-string])"/>
    <xsl:variable name="not-verified-results-count"
      select="count($all-testresults[.=$not-verified-string])"/>
    <xsl:variable name="total-results-count" select="count($all-testresults)"/>
    <xsl:variable name="full-results-percent"
      select="format-number($full-results-count div $total-results-count, '##0.#%')"/>
    <xsl:variable name="issues-results-percent"
       select="format-number($issues-results-count div $total-results-count, '##0.#%')"/>
    <xsl:variable name="not-verified-results-percent"
       select="format-number(($total-results-count - $full-results-count - $issues-results-count) div $total-results-count, '##0.#%')"/>

    <xsl:message>Full:         <xsl:value-of select="$full-results-count"/> (<xsl:value-of select="$full-results-percent"/>)</xsl:message>
    <xsl:message>Issues:       <xsl:value-of select="$issues-results-count"/> (<xsl:value-of select="$issues-results-percent"/>)</xsl:message>
    <xsl:message>Not verified: <xsl:value-of select="$not-verified-results-count"/> (<xsl:value-of select="$not-verified-results-percent"/>)</xsl:message>
    <xsl:message>Total:        <xsl:value-of select="$total-results-count"/></xsl:message>

    <h2 class="coloured5">
      <a name="{$testsuite-id}">
        <xsl:value-of select="@profile"/>
      </a>
    </h2>
    <table width="95%" style="text-align: center; align: center">
      <tr>
        <td class="full">Full</td>
        <td class="differ">Issues</td>
        <xsl:if test="$not-verified-results-count">
          <td class="not-yet-verified">Not yet verified</td>
        </xsl:if>
        <td class="coloured2" style="border-style: none">Total</td>
      </tr>
      <tr class="coloured">
        <td><xsl:value-of select="$full-results-count"/></td>
        <td>
          <xsl:value-of select="$issues-results-count"/>
        </td>
        <xsl:if test="$not-verified-results-count">
          <td>
            <xsl:value-of select="$not-verified-results-count"/>
          </td>
        </xsl:if>
        <td>
          <xsl:value-of select="count($all-testresults)"/>
        </td>
      </tr>
      <tr class="coloured">
        <td>
          <xsl:value-of select="$full-results-percent"/>
        </td>
        <td>
          <xsl:value-of select="$issues-results-percent"/>
        </td>
        <xsl:if test="$not-verified-results-count">
          <td>
            <xsl:value-of select="$not-verified-results-percent"/>
          </td>
        </xsl:if>
        <td>100%</td>
      </tr>
    </table>
    <xsl:if test="$REFERENCE">
      <table style="margin-top: 12pt; margin-bottom: 12pt">
        <xsl:variable name="tests-with-differences" select="count($testsuccess-node/directory/pdf/diff[*[@size != 0]])"/>
        <xsl:message><xsl:value-of select="$tests-with-differences"/> tests with differences</xsl:message>
        <tr class="coloured2">
          <td><xsl:value-of select="$tests-with-differences"/> tests with differences</td>
        </tr>
        <xsl:if test="$tests-with-differences > 0">
          <tr class="coloured">
            <td>
              <xsl:for-each select="$testsuccess-node/directory/pdf[diff/*[@size != 0]]">
                <xsl:sort/>
                <a href="{ancestor::directory/@name}/{substring-before(@name, '.pdf')}.html" target="_blank">
                  <xsl:value-of select="substring-before(@name, '.pdf')"/>
                </a>
                <xsl:text> </xsl:text>
              </xsl:for-each>
            </td>
          </tr>
        </xsl:if>
      </table>
    </xsl:if>
    <table>
      <xsl:apply-templates>
        <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      </xsl:apply-templates>
    </table>
  </xsl:template>

  <xsl:template match="testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr>
      <td colspan="5" class="coloured4">
        <h2>
          <a name="{$my-testcases-id}">
            <xsl:text/>Test Cases: <xsl:value-of select="@profile"/>
          </a>
        </h2>
      </td>
      <td class="coloured4">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
<!--
      <td>
        <form action="/xmlroff/{$BASENAME}/regenerate-testsuccess.pl" method="post">
          <input type="submit" name="submit" value="Regenerate"/>
        </form>
      </td>
-->
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testcases/testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr>
      <td colspan="5" class="coloured3">
        <h3>
          <a name="{$my-testcases-id}">
            <xsl:text/>Test Cases: <xsl:value-of select="@profile"/>
          </a>
        </h3>
      </td>
      <td class="coloured3">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
<!--
      <td>
        <form action="/xmlroff/{$BASENAME}/regenerate-testsuccess.pl" method="post">
          <input type="submit" name="submit" value="Regenerate"/>
        </form>
      </td>
-->
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testcases/testcases/testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr>
      <td colspan="5" class="coloured2">
        <h4>
          <a name="{$my-testcases-id}">
            <xsl:text/>Test Cases: <xsl:value-of select="@profile"/>
          </a>
        </h4>
      </td>
      <td class="coloured2">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
<!--
      <td>
        <form action="/xmlroff/{$BASENAME}/regenerate-testsuccess.pl" method="post">
          <input type="submit" name="submit" value="Regenerate"/>
        </form>
      </td>
-->
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testcases/testcases/testcases/testcases">
    <xsl:param name="my-testcases-id"
      select="translate(normalize-space(@profile), ' ', '-')"/>
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"
      select="$my-testcases-id"/>
    <xsl:param name="results-top-base" select="@base"/>

    <tr>
      <td colspan="5" class="coloured">
        <h4>
          <a name="{$my-testcases-id}">
            <xsl:text/>Test Cases: <xsl:value-of select="@profile"/>
          </a>
        </h4>
      </td>
      <td class="coloured">
        <xsl:call-template name="nav-table">
          <xsl:with-param name="top-id" select="$testsuite-id"/>
        </xsl:call-template>
      </td>
<!--
      <td>
        <form action="/xmlroff/{$BASENAME}/regenerate-testsuccess.pl" method="post">
          <input type="submit" name="submit" value="Regenerate"/>
        </form>
      </td>
-->
    </tr>

    <xsl:apply-templates>
      <xsl:with-param name="testsuite-id" select="$testsuite-id"/>
      <xsl:with-param name="top-testcases-id" select="$top-testcases-id"/>
      <xsl:with-param name="results-top-base" select="$results-top-base"/>
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="testresult">
    <xsl:param name="testsuite-id"/>
    <xsl:param name="top-testcases-id"/>
    <xsl:param name="results-top-base" select="(ancestor::*/@base)[1]"/>

    <xsl:variable name="testresult-id"
      select="concat('result-', $top-testcases-id, '-', translate(normalize-space(@id), ' ', '-'))"/>
    <xsl:variable name="id" select="@id"/>
    <xsl:variable name="results" select="@results"/>
    <tr>
      <xsl:if test="count(preceding-sibling::*) mod 2 = 1">
        <xsl:attribute name="class">coloured</xsl:attribute>
      </xsl:if>
      <td>
        <a name="{$testresult-id}">
          <xsl:value-of select="$id"/>
        </a>
      </td>
      <td>
        <xsl:call-template name="attribute-table"/>
      </td>
      <td>
        <xsl:copy-of select="*|text()"/>
      </td>
      <td>
        <xsl:if test="@results != ''">
          <a>
            <xsl:attribute name="href">
              <xsl:if test="ancestor::testcases/@base">
                <xsl:value-of select="(ancestor::testcases/@base)[1]"/>
                <xsl:text>/</xsl:text>
              </xsl:if>
              <xsl:value-of select="@results"/>
            </xsl:attribute>
            <xsl:text>PDF</xsl:text>
          </a>
        </xsl:if>
      </td>
      <td>
        <xsl:for-each select="$testsuccess-node">
          <xsl:variable name="pdf" select="key('PDF', $results)[ancestor::*/@name = $results/ancestor::*/@base]"/>
          <xsl:value-of select="$pdf"/>
          <a href="{($results/ancestor::*/@base)}/{$id}.html" target="_blank">Results</a>
          <xsl:call-template name="results-doc">
            <xsl:with-param name="pdf" select="$pdf"/>
            <xsl:with-param name="results" select="$results/.."/>
            <xsl:with-param name="results-top-base" select="$results-top-base"/>
            <xsl:with-param name="id" select="$id"/>
          </xsl:call-template>
        </xsl:for-each>
      </td>
      <td>
        <xsl:for-each select="$testsuccess-node">
          <xsl:variable name="pdf" select="key('PDF', $results)[ancestor::*/@name = $results/ancestor::*/@base]"/>
          <xsl:value-of select="$pdf"/>
          <xsl:choose>
            <xsl:when test="not($pdf) or $pdf/@size = 0">
              <xsl:text>No output</xsl:text>
            </xsl:when>
            <xsl:otherwise>
              <xsl:value-of select="$pdf/pwd/@count"/>
              <xsl:if test="$pdf/pwd/@count != 0">
                <xsl:text>, PNG</xsl:text>
              </xsl:if>
              <xsl:if test="$REFERENCE">
                <xsl:if test="$pdf/ref/@count != '0'">
                  <xsl:text>, Ref</xsl:text>
                </xsl:if>
                <xsl:if test="$pdf/diff/@count != 0">
                  <xsl:text>, </xsl:text>
                  <xsl:choose>
                    <xsl:when test="$pdf/diff/*[@size != 0]">
                      <span style="color: white; background-color: red">Diff</span>
                    </xsl:when>
                    <xsl:otherwise>
                      <xsl:text>Diff</xsl:text>
                    </xsl:otherwise>
                  </xsl:choose>
                </xsl:if>
                <xsl:if test="$pdf/stereo/@count != 0">
                  <xsl:text>, Stereo</xsl:text>
                </xsl:if>
              </xsl:if>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:for-each>
      </td>
    </tr>
  </xsl:template>

  <xsl:template name="results-doc">
    <xsl:param name="pdf"/>
    <xsl:param name="results"/>
    <xsl:param name="results-top-base"
      select="($results/ancestor::*/@base)[1]"/>
    <xsl:param name="id"/>

    <xsl:variable name="test"
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

    <xsl:if test="$OUTPUT_INDIVIDUAL = 'yes'">
      <saxon:output href="./{$results-top-base}/{$id}.html" encoding="UTF-8">
      <html>
        <head>
          <title>
            <xsl:value-of select="$results/ancestor::testsuite/@profile"/>
            <xsl:text>: </xsl:text>
            <xsl:for-each select="$results/ancestor::*/@base">
              <xsl:value-of select="."/>
              <xsl:text>/</xsl:text>
            </xsl:for-each>
            <xsl:value-of select="$id"/>
          </title>
          <style type="text/css">
    .coloured {background-color: #DDEEFF}
    .coloured2 {background-color: #CCDDFF}
    .coloured3 {background-color: #BBCCFF}
            body { background-color: grey}
            h1 { background-color: white}
            h2 { background-color: yellow}
	    span.png-title { font-size: 150%; font-weight: bold}
            tr.per-page-banner { background-color: yellow}
            <xsl:call-template name="coverage-styles"/>
          </style>
        </head>
        <body>
          <h1 class="coloured">
            <xsl:for-each select="$results/ancestor::*/@base">
              <xsl:value-of select="."/>
              <xsl:text>/</xsl:text>
            </xsl:for-each>
            <xsl:value-of select="$id"/>
          </h1>
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
                <b>Result </b>
                <xsl:choose>
                  <xsl:when test="$test/@result">
                    <xsl:call-template name="munged-a">
                      <xsl:with-param name="href" select="$test/@result"/>
                      <xsl:with-param name="content">
                        <xsl:value-of select="$test/@result"/>
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
                <a href="{$id}.pdf"><xsl:value-of select="$id"/>.pdf</a>
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
                  <a href="#page{position()}"><xsl:value-of select="position()"/></a>
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
                    <xsl:value-of select="$name"/>
                  </a>
                </td>
                <xsl:if test="$REFERENCE">
                  <xsl:if test="../../ref/png[@name=$name]">
                    <td>
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
    </saxon:output>
    </xsl:if>
  </xsl:template>

  <xsl:template name="attribute-table">
    <table border="1" width="100%">
      <tr>
        <td align="center" width="33%">
          <xsl:attribute name="class">
            <xsl:choose>
              <xsl:when test="@agreement = 'issues' and . = $not-verified-string">
                <xsl:text/>other</xsl:when>
              <xsl:when test="@agreement = 'full'">
                <xsl:text/>full</xsl:when>
              <xsl:otherwise>differ</xsl:otherwise>
            </xsl:choose>
          </xsl:attribute>
          <xsl:choose>
            <xsl:when test="@agreement = 'issues' and . = $not-verified-string">
              <xsl:text/>&#160;</xsl:when>
            <xsl:when test="@agreement = 'full'">
              <xsl:text>Full</xsl:text>
            </xsl:when>
            <xsl:otherwise>Issues</xsl:otherwise>
          </xsl:choose>
        </td>
        <td align="center" width="34%">
          <xsl:attribute name="class">
            <xsl:choose>
              <xsl:when test="@specproblem = 'yes'">
                <xsl:text/>spec</xsl:when>
              <xsl:otherwise>other</xsl:otherwise>
            </xsl:choose>
          </xsl:attribute>
          <xsl:choose>
            <xsl:when test="@specproblem = 'yes'">
              <xsl:text/>Spec</xsl:when>
            <xsl:otherwise>&#160;</xsl:otherwise>
          </xsl:choose>
        </td>
        <td align="center" width="33%">
          <xsl:attribute name="class">
            <xsl:choose>
              <xsl:when test="@testproblem = 'yes'">
                <xsl:text>test</xsl:text>
	      </xsl:when>
              <xsl:otherwise>other</xsl:otherwise>
            </xsl:choose>
          </xsl:attribute>
          <xsl:choose>
            <xsl:when test="@testproblem = 'yes'">
              <xsl:text>Test</xsl:text>
	    </xsl:when>
            <xsl:otherwise>&#160;</xsl:otherwise>
          </xsl:choose>
        </td>
      </tr>
    </table>
  </xsl:template>


  <xsl:template name="munged-a">
    <xsl:param name="href"/>
    <xsl:param name="content"/>
    <xsl:param name="test-file-dirname"/>

    <xsl:variable name="href-dirname">
      <xsl:call-template name="dirname">
        <xsl:with-param name="string" select="$href"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="full-href">
      <xsl:call-template name="merge-dirnames">
        <xsl:with-param name="dirname1" select="$test-file-dirname"/>
        <xsl:with-param name="dirname2" select="$href-dirname"/>
			</xsl:call-template>
      <xsl:call-template name="basename">
        <xsl:with-param name="string" select="$href"/>
      </xsl:call-template>
    </xsl:variable>

    <xsl:variable name="use-href">
      <xsl:choose>
        <xsl:when test="starts-with($full-href, '/usr/local/src/xslfo')">
          <xsl:text>/xmlroff</xsl:text>
          <xsl:value-of select="substring-after($full-href, 'usr/local/src/xslfo')"/>
        </xsl:when>
        <xsl:when test="starts-with($full-href, '/usr/local/src/TestSuite')">
          <xsl:text>/xmlroff</xsl:text>
          <xsl:value-of select="substring-after($full-href, 'usr/local/src')"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$full-href"/>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:variable>

    <xsl:if test="$DEBUG">
      <xsl:message>munged-a:: full-href: '<xsl:value-of select="$full-href"/>; test-file-dirname: '<xsl:value-of select="$test-file-dirname"/>'</xsl:message>
      <xsl:message>munged-a:: use-href: '<xsl:value-of select="$use-href"/>; content: '<xsl:value-of select="$content"/>'</xsl:message>
    </xsl:if>
    
    <a href="{$use-href}">
      <xsl:copy-of select="$content"/>
    </a>
  </xsl:template>

  <xsl:template name="results-form">
    <xsl:param name="results"/>
    <xsl:param name="id"/>
    <xsl:param name="results-top-base"/>
    <table bgcolor="white" border="0" cellspacing="0">
      <xsl:for-each select="$results">
        <form action="/xmlroff/{$BASENAME}/update-results.pl" method="post">
          <input type="hidden" name="id" value="{$id}"/>
          <input type="hidden" name="top-base" value="{$results-top-base}"/>
          <input type="hidden" name="path" value="{($results/ancestor::*/@base)[1]}/{$id}"/>
          <tr>
            <td style="background-color: white">Agreement:</td>
            <td style="background-color: white">
              <select name="agreement">
                <option value="full">
                  <xsl:if test="@agreement='full'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Full</xsl:text>
                </option>
                <option value="issues">
                  <xsl:if test="@agreement='issues'">
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
                  <xsl:if test="@futuresupport='full'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Full</xsl:text>
                </option>
                <option value="partial">
                  <xsl:if test="@futuresupport='partial'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Partial</xsl:text>
                </option>
                <option value="none">
                  <xsl:if test="@futuresupport='none'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>None</xsl:text>
                </option>
                <option>
                  <xsl:if test="not(@futuresupport)">
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
                  <xsl:if test="@specproblem='yes'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Yes</xsl:text>
                </option>
                <option value="no">
                  <xsl:if test="not(@specproblem) or @specproblem='no'">
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
                  <xsl:if test="@testproblem='yes'">
                    <xsl:attribute name="selected">selected</xsl:attribute>
                  </xsl:if>
                  <xsl:text>Yes</xsl:text>
                </option>
                <option value="no">
                  <xsl:if test="not(@testproblem) or @testproblem='no'">
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
        </form>
      </xsl:for-each>
    </table>
  </xsl:template>

  <xsl:template name="results-static">
    <table bgcolor="white" border="0" cellspacing="0">
      <xsl:for-each select="$results">
        <tr>
          <td style="background-color: white">Agreement:</td>
          <td width="10%">
            <xsl:attribute name="class">
              <xsl:choose>
                <xsl:when test="@agreement = 'issues' and . = $not-verified-string">
                  <xsl:text>other</xsl:text>
		</xsl:when>
                <xsl:when test="@agreement = 'full'">
                  <xsl:text>full</xsl:text>
		</xsl:when>
                <xsl:otherwise>
		  <xsl:text>differ</xsl:text>
		</xsl:otherwise>
              </xsl:choose>
            </xsl:attribute>
            <xsl:choose>
              <xsl:when test="@agreement = 'full'">
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
              <xsl:when test="@futuresupport = 'full'">
                <xsl:text>Full</xsl:text>
              </xsl:when>
              <xsl:when test="@futuresupport = 'partial'">
                <xsl:text>Partial</xsl:text>
              </xsl:when>
              <xsl:when test="not(@futuresupport)">
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
                <xsl:when test="@specproblem = 'yes'">
                  <xsl:text>spec</xsl:text>
		</xsl:when>
            	<xsl:otherwise>other</xsl:otherwise>
	      </xsl:choose>
    	    </xsl:attribute>
            <xsl:choose>
              <xsl:when test="@specproblem = 'yes'">
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
                <xsl:when test="@testproblem = 'yes'">
                  <xsl:text>test</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:text>other</xsl:text>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:attribute>
            <xsl:choose>
              <xsl:when test="@testproblem = 'yes'">
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
            <xsl:value-of select="."/>
          </td>
        </tr>
      </xsl:for-each>
    </table>
  </xsl:template>

</xsl:stylesheet>
